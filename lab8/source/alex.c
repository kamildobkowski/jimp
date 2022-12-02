#include "alex.h"

#include <ctype.h>

static int ln = 0;
static char ident[256];
static FILE *ci = NULL;

// zeruje zmienne dla nowego pliku zmienne dla pliku
void alex_init4file(FILE *in)
{
	ln = 0;
	ci = in;
}

int isKeyword(char *indentyfier)
{
	return 1;
}

// Wybiera następny znak z pliku źródłowego i zwraca jeden ze statusów enuma lexem_t
lexem_t alex_nextLexem(void)
{
	int c;
	// Pętla kończąca zadanie kiedy przejdzie przez wszystkie znaki w pliku
	while ((c = fgetc(ci)) != EOF)
	{
		// Ignorujemy wszystkie spacje w pliku
		if (isspace(c))
			continue;
		else if (c == '\n') // Jeśli znajdziemy znak nowej lini zwiększamy naszą zmienną
			ln++;
		// START: Definicji działań zwracających wartości enuma lexem_t
		else if (c == '(')
			return OPEPAR;
		else if (c == ')')
			return CLOPAR;
		else if (c == '{')
			return OPEBRA;
		else if (c == '}')
			return CLOBRA;
		// Przy wykryciu znaku alfanumerycznego wiemy że będzie on identyfikatorem zmiennej, funckcji, funkcji pomijalnej itp
		else if (isalpha(c))
		{
			int i = 1;
			ident[0] = c;
			while (isalnum(c = fgetc(ci)))
				ident[i++] = c;
			ident[i] = '\0';
			return isKeyword(ident) ? OTHER : IDENT;
		}
		else if (c == '"')
		{
			/* Uwaga: tu trzeba jeszcze poprawic obsluge nowej linii w trakcie napisu
			   i \\ w napisie
			*/
			int cp = c;
			while ((c = fgetc(ci)) != EOF && c != '"' && cp == '\\')
			{
				cp = c;
			}
			return c == EOF ? EOFILE : OTHER;
		}
		else if (c == '/')
		{
			/* moze byc komentarz */
		}
		if (isdigit(c) || c == '.')
		{
			/* liczba */
		}
		else
		{
			return OTHER;
		}
	}
	return EOFILE;
}

// Zwraca aktulny indetyfikator funkcji w której się znajdujemy
char *alex_ident(void)
{
	return ident;
}

// Zwraca linie w której się znajdujemy
int alex_getLN()
{
	return ln;
}
