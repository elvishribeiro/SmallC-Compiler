//tokens.h
#include <stdio.h>

#define _PCOMMA 		1
#define _COMMA 			2
#define _LBRACKET 		3
#define _RBRACKET 		4
#define _LBRACE 		5
#define _RBRACE 		6
#define _ATTR 			7
#define _PLUS			8
#define _MINUS			9
#define _MULT 			10
#define _DIV 			11
#define _LCOL 			12
#define _RCOL			13 
#define _INTEGER_CONST 	14
#define _FLOAT_CONST 	15
#define _EQ				16
#define _LT 			17
#define _LE 			18
#define _GT 			19
#define _GE 			20
#define _ID				21
#define _MAIN 			22
#define _INT 			23
#define _FLOAT  		24
#define _IF 			25
#define _ELSE 			26
#define _WHILE 			27
#define _FOR 			28
#define _READ 			29
#define _PRINT 			30

#define _BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define _BOLDGREEN   "\033[1m"      /* Bold Green */
#define _RESET   "\x1b[0m"

#define TRUE 1
#define FALSE 0


typedef struct simbolo{
	int tipo;
	char *lexema;
	int linha;

}simbolo_t;


typedef struct token_s{
	int nome;
	char *lexema;
	int linha;
}token_t;

//analisadores
int analisadorSintatico(token_t* tokensAux, int numTokensAux);
token_t* analisadorLexico(FILE *fonte, int *numTokens);

//funções IO
char getNextChar(FILE *arq);
void resetBuff();

//converte int para string
char *numToToken(int num);