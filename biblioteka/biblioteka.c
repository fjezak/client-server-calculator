/*
 ============================================================================
 Name        : serwer.c
 Author      : Dominik Seweryn
 Version     : 1.0.0
 Created	 : 04.11.2016
 Description : Projekt na PjC2
 ============================================================================
 */
#include "biblioteka.h"

#define ERROR 1

int dodawanie(int a, int b) { return a+b; }
int odejmowanie(int a, int b) { return a-b; }
int mnozenie(int a, int b) { return a*b; }
int dzielenie(int a, int b) { return a/b; }

/**
 * @desc: funkcja przetwarza C-stringa na argumenty do wykonania wybranej operacji arytmetycznej,
 * następnie wpisuje rezultat do bufora wyjściowego.
 * @param wej - bufor wejściowy - oczekuje danych w formacje {a} {+, -, *, /} {b}
 * @param wyj - bufor wyjściowy - formatuje rezultat {a} {+, -, *, /} {b} = {c}
 * @return wskanik na bufor wyjściowy
 *
 */
char *funkcja(char *wej, char *wyj) {
	int (*wsk_func)(int, int);
	char *args[3];
	char *operacja;
	int a, b;
	int len = strlen(wej);
	int i, spaces = 0;
	int mark = 0;
	int size = 0;
	int err = 0;

	for(i = 0; i < len; i++) {
		if(wej[i] == ' ') {
			size = i - mark; // długość argumentu
			args[spaces] = malloc(size + 1); //utworzenie bufora na argument
			memcpy(args[spaces], wej + mark, size); //skopiowanie danych do bufora
			args[spaces][size] = '\0'; //dodanie zera na końcu oznaczającego koniec C-stringa
			spaces++; //zliczanie wystąpień znaku spacji
			mark = i+1; //znacznik ustawiony na początku kolejnego argumentu
			if(spaces > 2) break;
		}
	}
	if(spaces != 2) {
		sprintf(wyj, "Niepoprawne wywołanie. Składnia: 'arg1' 'znak' 'arg2'\n");
		err = ERROR;
	}
	if(!err) {
		/**
		 * Ostatni argument kopiowany poza pętlą.
		 */
		size = len - mark;
		args[spaces] = malloc(size + 1);
		memcpy(args[spaces], wej + mark, size);
		args[spaces][size] = '\0';

		a = atoi(args[0]);
		if(a == 0 && ( args[0][0] != '0' )) {
			sprintf(wyj, "arg1 to nie liczba\n");
			err = ERROR;
		}
		b = atoi(args[2]);
		if(b == 0 && ( args[2][0] != '0' )) {
			sprintf(wyj, "arg2 to nie liczba\n");
			err = ERROR;
		}
		operacja = args[1];
	}
	if(!err) {
		if(strcmp(operacja, "+") == 0) {
			wsk_func = &dodawanie;
		} else if(strcmp(operacja, "-") == 0) {
			wsk_func = &odejmowanie;
		} else if(strcmp(operacja, "*") == 0) {
			wsk_func = &mnozenie;
		} else if(strcmp(operacja, "/") == 0) {
			if(b == 0) {
				sprintf(wyj, "%d %s %d = NaN\n", a, operacja, b);
				err = ERROR;
			}
			wsk_func = &dzielenie;
		} else {
			sprintf(wyj, "Niepoprawne działanie. Obsługiwane: '+', '-', '*', '/'\n");
			err = ERROR;
		}
	}

	if(!err) {
		sprintf(wyj, "%d %s %d = %d\n", a, operacja, b, wsk_func(a, b));
	}

	if(spaces > 0) free(args[0]);
	if(spaces > 1) free(args[1]);
	if(spaces > 2) free(args[2]);

	puts(wyj);

	return wyj;
}
