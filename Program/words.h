#ifndef __WORDS_H_
#define __WORDS_H_


typedef struct {
    char *word;
    int len;
} Word;

/*
 * Retorna una copia del string [ word ].
 */
Word * word_copy(Word *w);

/*
 * Retorna la comparacion entre los strings [ word1 ] y [ word2 ].
 */
int word_compare(Word *word1, Word *word2);

/*
 * Destruye el string [ word ].
 */
void word_destroy(Word *w);

/*
 * Imprime por pantalla el string [ word ].
 */
void word_print(Word *w);

/**
 * Funcion de hash para strings propuesta por Kernighan & Ritchie en "The C
 * Programming Language (Second Ed.)".
 */
unsigned word_hash(Word *word);


/*
 * Retorna 1 si el caracter [ c ] no se encuentra en el alfabeto minusculo.
 */
int invalid_character(char c);





#endif