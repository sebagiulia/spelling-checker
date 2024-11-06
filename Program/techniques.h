#ifndef __TECHNIQUES_H_
#define __TECHNIQUES_H_

/**
 * Tecnica que intercambia cada par adyacente caracteres sobre una palabra y evalua la nueva palabra a partir de la funcion 
 * [ check_word ]. Si la lista de sugerencias alcanza el limite establecido la funcion termina retornando 1.
 */
int swapping_technique(Word *w, HashTable dTable, HashTable *distTables, WList *suggestions, int *lenS, int dist, int cd);

/**
 * Tecnica que reemplaza cada caracter de una palabra por caracteres de un alfabeto y evalua la nueva  
 * palabra a partir de la funcion [ check_word ]. Si la lista de sugerencias alcanza el limite establecido la 
 * funcion termina retornando 1.
 */
int replacing_technique(Word *w, HashTable dTable, HashTable *distTables, WList *suggestions, int *lenS, int dist, int cd);

/**
 * Tecnica que elimina cada caracter de una palabra y evalua la nueva palabra a partir de la funcion 
 * [ check_word ]. Si la lista de sugerencias alcanza el limite establecido la funcion termina retornando 1.
 */
int removing_technique(Word *w, HashTable dTable, HashTable *distTables, WList *suggestions, int *lenS, int dist, int cd);

/**
 * Tecnica que inserta cada caracter de un alfabeto en cualquier posicion de una palabra y evalua la nueva palabra a partir 
 * de la funcion [ check_word ]. Si la lista de sugerencias alcanza el limite establecido la funcion termina retornando 1.
 */
int insertion_technique(Word *w, HashTable dTable, HashTable *distTables, WList *suggestions, int *lenS, int dist, int cd);

/**
 * Tecnica que divide una palabra en dos y busca cada una en un diccionario, si ambas se encuentran, se agregan como una frase
 * a la lista de sugerencias. Si la lista de sugerencias alcanza el limite establecido la funcion termina retornando 1.
 */
int splitting_technique(Word *w, HashTable dTable, WList *suggestions, int *lenS);

/**
 * Remueve un caracter de un string en la posicion i.
 */
void remove_letter(char *buff, int i);

/**
 * Intercambia dos caracteres de un string en las posiciones i1 e i2.
 */
void swap_letters(char *buff, int i1, int i2);

/**
 * Agrega un caracter a un string en la posicion i.
 */
void add_letter(char *s, int len, int i, char letter);

/**
 * Divide un string en dos subs-strings en la posicion i y los almacena sobre word1 y word2.
 */
void split_words(char *buff, int len, int i, char *word1, char *word2);

#endif