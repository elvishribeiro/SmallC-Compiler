//analisadorLéxico.c

/* Simple Small-C Compiler 
 *  
 * Copyright (C) 2019 Elvis H. Ribeiro <elvishribeiro@gmail.com> 
 *  
 * All rights reserved. 
 *  
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met: 
 *  
 * * Redistributions of source code must retain the above copyright notice, 
 *   this list of conditions and the following disclaimer. 
 *  
 * * Redistributions in binary form must reproduce the above copyright notice, 
 *   this list of conditions and the following disclaimer in the documentation 
 *   and/or other materials provided with the distribution. 
 *  
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR 
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON 
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef HEADER
#define HEADER
#include "header.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


int numero(char numero){
	if (numero >= '0' & numero <= '9')	return TRUE;
	return FALSE;
}

int letra(char letra){
	if ((letra >= 'a' && letra <= 'z') || (letra >= 'A' && letra <= 'Z')) return TRUE;
	return FALSE;
}

//verifica se é uma palavra reservada
int palavraReservada(char *palavra){					
	if (strcmp(palavra, "main") == 0) return _MAIN;
	if (strcmp(palavra, "int") == 0) return _INT;
	if (strcmp(palavra, "float") == 0) return _FLOAT;
	if (strcmp(palavra, "if") == 0) return _IF;
	if (strcmp(palavra, "else") == 0) return _ELSE;
	if (strcmp(palavra, "while") == 0) return _WHILE;
	if (strcmp(palavra, "for") == 0) return _FOR;
	if (strcmp(palavra, "read") == 0) return _READ;
	if (strcmp(palavra, "print") == 0) return _PRINT;
	return _ID;
}


void novoToken(token_t*tokens, int *numTokens, int nome, char *lexema, int linha){
	tokens[*numTokens].nome = nome;
	tokens[*numTokens].lexema = malloc(sizeof(lexema)*sizeof(char));
	strcpy(tokens[*numTokens].lexema, lexema);
	tokens[*numTokens].linha = linha;
	(*numTokens)++;
}

token_t* analisadorLexico(FILE *fonte, int *numTokens){
	int state = 0;

	int tokensTAM = 2;
	token_t*tokens = malloc (tokensTAM*sizeof(token_t));


	char c;
	char *lexema = (char*) malloc(254*sizeof(char));
	int lexemaCont = 0;
	int ler = 1;

	*(numTokens) = 0;
	int linha = 1;

	resetBuff();
	while (!feof(fonte)){
		if (ler)
			c = getNextChar(fonte);
		else 
			ler = 1;
	
		if (c == '\n'){		//conta as linhas
			linha++;
		}

		switch (state){
			case 0:
				lexemaCont = 0;
				if (c == ';'){
					lexema[0] = c;
					lexema[1] = '\0';
					novoToken(tokens, numTokens, _PCOMMA, lexema, linha);
				}
				else if (c == ','){
					lexema[0] = c;
					lexema[1] = '\0';
					novoToken(tokens, numTokens, _COMMA, lexema, linha);
				}
				else if (c == '('){
					lexema[0] = c;
					lexema[1] = '\0';
					novoToken(tokens, numTokens, _LBRACKET, lexema, linha);
				}
				else if (c == ')'){
					lexema[0] = c;
					lexema[1] = '\0';
					novoToken(tokens, numTokens, _RBRACKET, lexema, linha);
				}
				else if (c == '{'){
					lexema[0] = c;
					lexema[1] = '\0';
					novoToken(tokens, numTokens, _LBRACE, lexema, linha);
				}
				else if (c == '}'){
					lexema[0] = c;
					lexema[1] = '\0';
					novoToken(tokens, numTokens, _RBRACE, lexema, linha);
				}
				else if (c == '='){
					lexema[0] = c;
					state = 7;
				}
				else if (c == '<'){
					lexema[0] = c;
					state = 4;
				}
				else if (c == '>'){
					lexema[0] = c;
					state = 5;
				}
				else if (c == '+'){
					lexema[0] = c;
					lexema[1] = '\0';
					novoToken(tokens, numTokens, _PLUS, lexema, linha);
				}
				else if (c == '-'){
					lexema[0] = c;
					lexema[1] = '\0';
					novoToken(tokens, numTokens, _MINUS, lexema, linha);
				}
				else if (c == '*'){
					lexema[0] = c;
					lexema[1] = '\0';
					novoToken(tokens, numTokens, _MULT, lexema, linha);
				}
				else if (c == '/'){
					lexema[0] = c;
					lexema[1] = '\0';
					novoToken(tokens, numTokens, _DIV, lexema, linha);
				}
				else if (c == '['){
					lexema[0] = c;
					lexema[1] = '\0';
					novoToken(tokens, numTokens, _LCOL, lexema, linha);
				}
				else if (c == ']'){
					lexema[0] = c;
					lexema[1] = '\0';
					novoToken(tokens, numTokens, _RCOL, lexema, linha);
				}
				else if (numero(c)){
					lexema[lexemaCont++] = c;
					state = 1;
				}
				else if (letra(c)){
					lexema[lexemaCont++] = c;
					state = 6;
				}else if (c != ' ' && c != '	' && c != '\n'){
					lexema[lexemaCont++] = c;
					state = 8;
				}
				
				break;


			//estados para detecção de numeros

			//analisa inteiros
			case 1:
				if (numero(c)){
					lexema[lexemaCont++] = c;
				}
				else if (c == '.'){
					lexema[lexemaCont++] = c;
					state = 2;
				}else{
					lexema[lexemaCont] = '\0';
					novoToken(tokens, numTokens, _INTEGER_CONST, lexema, linha);
					ler = 0;								//evita de avançar um caractere
					state = 0;	
				}
				break;

			//analisa floats
			case 2:
				if (numero(c)){
					lexema[lexemaCont++] = c;
					state = 3;
				}else{
					//erro de sintaxe
					state = 0;
				}
				break;

			//casas depois do ponto do float
			case 3:
				if (numero(c)){
					lexema[lexemaCont++] = c;
				}else{
					lexema[lexemaCont] = '\0';
					novoToken(tokens, numTokens, _FLOAT_CONST, lexema, linha);
					ler = 0;
					state = 0;
				}
				break;

			//estados para classificação de <, <=
			case 4:
				if (c == '=') {
					lexema[1] = c;
					lexema[2] = '\0';
					novoToken(tokens, numTokens, _LE, lexema, linha);
				}else{
					lexema[1] = '\0';
					novoToken(tokens, numTokens, _LT, lexema, linha);
				}
				state = 0;
				break;

			case 5:
				if (c == '=') {
					lexema[1] = c;
					lexema[2] = '\0';
					novoToken(tokens, numTokens, _GE, lexema, linha);
				}else{
					lexema[1] = '\0';
					novoToken(tokens, numTokens, _GT, lexema, linha);
				}
				state = 0;
				break;

			//Detecção de ID ou comando
			case 6:
				if (letra(c) | numero(c) | c == '_'){
					lexema[lexemaCont++] = c;
				}else {
					lexema[lexemaCont] = '\0';
					novoToken(tokens, numTokens, palavraReservada(lexema), lexema, linha);
					ler = 0;
					state = 0;
				}
				break;

			//EQ ou attr
			case 7:
				if (c == '=') {
					lexema[1] = c;
					lexema[2] = '\0';
					novoToken(tokens, numTokens, _EQ, lexema, linha);
				}else{
					lexema[1] = '\0';
					novoToken(tokens, numTokens, _ATTR, lexema, linha);
				}
				state = 0;
				break;

			//tokens desconhecidos
			case 8: 
				if (c == ' ' || c == '\n'){
					lexema[lexemaCont]='\0';
					//novoToken(tokens, numTokens, -1, lexema, linha);
					printf(_BOLDGREEN "line %d: " _BOLDRED "error: " _RESET "stray ‘"_BOLDGREEN"%s"_RESET"’ in program\n", linha, lexema);

					ler = 0;
					state = 0;
				}else{
					lexema[lexemaCont++] = c;
				}
		}

		//heuristica pra alocar memoria para os tokens
		if (*numTokens == tokensTAM){
			tokensTAM *= 2;
			tokens =  realloc(tokens, tokensTAM*sizeof(token_t));
		}
	}
	
	//printTokens(tokens, *(numTokens));

	return tokens;
}

