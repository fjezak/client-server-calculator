/*
 ============================================================================
 Name        : serwer.c
 Author      : Dominik Seweryn
 Version     : 1.0.0
 Created	 : 04.11.2016
 Description : Projekt na PjC2
 ============================================================================
 */

#ifndef BIBLIOTEKA_H_
#define BIBLIOTEKA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @desc: funkcja przetwarza C-stringa na argumenty do wykonania wybranej operacji arytmetycznej,
 * następnie wpisuje rezultat do bufora wyjściowego.
 * @param wej - bufor wejściowy - oczekuje danych w formacje {a} {+, -, *, /} {b}
 * @param wyj - bufor wyjściowy - formatuje rezultat {a} {+, -, *, /} {b} = {c}
 * @return wskanik na bufor wyjściowy
 */
char *funkcja(char *wej, char *wyj);


#endif /* BIBLIOTEKA_H_ */
