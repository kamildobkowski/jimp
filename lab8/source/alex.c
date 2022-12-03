#include "../include/alex.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int ln = 0;
static char ident[256];
static FILE *ci = NULL;

// zeruje zmienne dla nowego pliku zmienne dla pliku
void alex_init4file(FILE *in) {
    ln = 0;
    ci = in;
}

int isKeyword(char *indentyfier) {
    const char *keywords[] = {
        "auto",     "break",    "case",    "char",   "continue", "do",
        "default",  "const",    "double",  "else",   "enum",     "extern",
        "for",      "if",       "goto",    "float",  "int",      "long",
        "register", "return",   "signed",  "static", "sizeof",   "short",
        "struct",   "switch",   "typedef", "union",  "void",     "while",
        "volatile", "unsigned", "include"

    };
    int i;
    for (i = 0; i < 33; i++) {
        if (strcmp(indentyfier, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Wybiera następny znak z pliku źródłowego i zwraca jeden ze statusów enuma
// lexem_t
lexem_t alex_nextLexem(void) {
    int c;

    // Pętla kończąca zadanie kiedy przejdzie przez wszystkie znaki w pliku
    while ((c = fgetc(ci)) != EOF) {
        //  Ignorujemy wszystkie spacje w pliku
        if (c == '\n') {
            ln++;
            continue;
        } else if (isspace(c))
            continue;
        // Jeśli znajdziemy znak nowej lini zwiększamy naszą zmienną

        // START: Definicji działań zwracających wartości enuma lexem_t
        else if (c == '(')
            return OPEPAR;
        else if (c == ')')
            return CLOPAR;
        else if (c == '{')
            return OPEBRA;
        else if (c == '}')
            return CLOBRA;
        // Przy wykryciu znaku alfanumerycznego wiemy że będzie on
        // identyfikatorem zmiennej, funckcji, funkcji pomijalnej itp
        else if (isalpha(c)) {
            int i = 1;
            ident[0] = c;
            while (isalnum(c = fgetc(ci)) || c == '_') ident[i++] = c;
            ident[i] = '\0';
            fseek(ci, -1L, SEEK_CUR);
            return isKeyword(ident) ? OTHER : IDENT;
        } else if (c == '"') {
            /* Uwaga: tu trzeba jeszcze poprawic obsluge nowej linii w trakcie
               napisu i \\ w napisie
            */
            int cp = c;
            while ((c = fgetc(ci)) != EOF && c != '"') {
                if (cp == '\\' && c == 'n') ln++;
                cp = c;
            }
            return c == EOF ? EOFILE : OTHER;
        } else if (c == '/') {
            /* moze byc komentarz */
            if (c = fgetc(ci) == '/') {
                while (c = fgetc(ci) != '\n')
                    ;
                ln++;
                continue;
            } else if (c == '*') {
                c = fgetc(ci);
                char next = fgetc(ci);
                while (!(c == '*' && next == '/')) {
                    if (c == '\n') ln++;
                    if (next == '\n') ln++;
                    c = next;
                    next = fgetc(ci);
                }
                continue;
            }
        }
        if (isdigit(c) || c == '.') {
            continue;
        } else {
            return OTHER;
        }
    }
    return EOFILE;
}

// Zwraca aktulny indetyfikator funkcji w której się znajdujemy
char *alex_ident(void) { return ident; }

// Zwraca linie w której się znajdujemy
int alex_getLN() { return ln; }
