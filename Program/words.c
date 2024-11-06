#include "words.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Word *word_copy(Word *w)
{
  Word *newWord = malloc(sizeof(Word));
  newWord->len = w->len;
  newWord->word = malloc(w->len + 1);
  memcpy(newWord->word, w->word, w->len + 1);
  return newWord;
}

int word_compare(Word *w1, Word *w2)
{
  return strcmp(w1->word, w2->word);
}

void word_destroy(Word *w)
{
  free(w->word);
  free(w);
}

void word_print(Word *w)
{
  printf("%s\n", w->word);
}

unsigned word_hash(Word *w)
{
  char *word = w->word;
  unsigned hashval;
  for (hashval = 0; *word != '\0'; ++word)
  {
    hashval = *word + 31 * hashval;
  }
  return hashval;
}

/////////////////////////////////////////////////////////////////////////

int invalid_character(char c)
{
  return !((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
