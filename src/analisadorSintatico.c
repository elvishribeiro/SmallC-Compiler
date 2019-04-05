//analisadorSintático

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

#include "hash.h"
#ifndef HEADER
#define HEADER
#include "header.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int Programa();
int Declaracao();
int Decl_Comando();
int Declaracao();
int Decl2();
int Tipo();

int Comando();
int Bloco();
int Atribuicao();
int ComandoSe();
int ComandoSenao();
int ComandoEnquanto();
int ComandoRead();
int ComandoPrint();
int ComandoFor();
int AtribuicaoFor();

int Expressao();
int RelacaoOpc();
int OpRel();
int Adicao();
int AdicaoOpc();
int OpAdicao();
int Termo();
int TermoOpc();
int OpMult();
int Fator();

simbolo_t* newSimbolo(token_t *token);
int printsimbolo(any_t ignore, any_t item);
int existeSimbolo(char *lexema);

int i = 0;
token_t *tokenEntrada;
token_t *tokens;
int numTokens;
int tipo;
map_t symb_tab;

simbolo_t* newSimbolo(token_t *token){
	simbolo_t *simbolo = malloc(sizeof(simbolo_t));
	if (token == NULL){
		simbolo->tipo = -1;
		simbolo->lexema = "";
		simbolo->linha = -1;
		return simbolo;
	}
	simbolo->tipo = tipo;
	simbolo->lexema = malloc((strlen(token->lexema))*sizeof(char));
	memcpy(simbolo->lexema, token->lexema, sizeof(simbolo->lexema)+1);
	simbolo->linha = token->linha;
	return simbolo;
}


int printsimbolo(any_t ignore, any_t item){
	if (item == NULL)
		return -1;

	simbolo_t *simbolo = (simbolo_t*)item;
	printf("Lexema: %-10s Tipo: %-6s Linha:%-5d\n", simbolo->lexema, numToToken(simbolo->tipo), simbolo->linha);

	return MAP_OK;
}

int existeSimbolo(char *lexema){
	simbolo_t *value = newSimbolo(NULL);
	if (hashmap_get(symb_tab, lexema, (any_t)value) == MAP_OK){
		free(value);
		return 1;
	}
	free(value);
	return 0;
}

int analisadorSintatico(token_t* tokensAux, int numTokensAux){
	i = 0;
	tokens = tokensAux;
	numTokens = numTokensAux;
	tokenEntrada = &(tokens[i]);
	symb_tab = hashmap_new();
	hashmap_put	(symb_tab, "", newSimbolo(NULL));				//initialize the hasmap
	
	Programa();
	printf("\n\nTABELA DE SÍMBOLOS\n");
	hashmap_iterate(symb_tab, printsimbolo, NULL);
}

int casa(int tokenEsperado){
	if (tokenEntrada->nome == tokenEsperado){
		if (tokenEntrada->nome == _ID){
			if (!existeSimbolo(tokenEntrada->lexema))
				printf(_BOLDGREEN "line %d: " _BOLDRED "error: " _RESET "‘"
			_BOLDGREEN "%s"_RESET"’ undeclared.\n", tokenEntrada->linha, tokenEntrada->lexema);
		}
		i++;
		tokenEntrada = &(tokens[i]);
		return 1;
	}else{
		printf(_BOLDGREEN "line %d: " _BOLDRED "error: " _RESET "expected ‘"_BOLDGREEN "%s"_RESET
			"’ before ‘"_BOLDGREEN"%s" _RESET"’.\n", tokenEntrada->linha, numToToken(tokenEsperado), tokenEntrada->lexema);
		return 0;
	}
}

int Programa (){
	//printf("Programa-> "); //remover
	casa(_INT);
	casa(_MAIN);
	casa(_LBRACKET);
	casa(_RBRACKET);
	casa(_LBRACE);
	Decl_Comando();
	casa(_RBRACE);
}

int Decl_Comando(){
	//printf("Decl_Comando-> "); //remover
	if (tokenEntrada->nome == _INT || tokenEntrada->nome == _FLOAT){
		Declaracao();
		Decl_Comando();
	}else if(tokenEntrada->nome == _LBRACE || tokenEntrada->nome == _ID || tokenEntrada->nome == _IF || 
				tokenEntrada->nome == _WHILE || tokenEntrada->nome == _READ || tokenEntrada->nome == _PRINT || 
				tokenEntrada->nome == _FOR){
		Comando();
		Decl_Comando();
	}else{}	
}

int Declaracao(){
	//printf("Declaracao-> Tipo ID Decl2-> "); //remover
	tipo = Tipo();
	token_t *tokenBackup = tokenEntrada;
	//insere na tabela de simbolos

	if (casa(_ID)){
		if (!existeSimbolo(tokenBackup->lexema)){
				simbolo_t *simbolo = newSimbolo(tokenBackup);
				hashmap_put(symb_tab, simbolo->lexema, simbolo);
		}else{
			printf(_BOLDGREEN "line %d: " _BOLDRED "error: " _RESET "redeclaration of  ‘"
				_BOLDGREEN "%s"_RESET"’.\n", tokenBackup->linha, tokenBackup->lexema);
		}
	}
	Decl2();
	tipo = -1;
}

int Decl2(){
	//printf("Decl2-> "); //remover
	if (tokenEntrada->nome == _COMMA){
		casa(_COMMA);
		token_t *tokenBackup = tokenEntrada;

		if (casa(_ID)){
			if (!existeSimbolo(tokenBackup->lexema)){
				simbolo_t *simbolo = newSimbolo(tokenBackup);
				hashmap_put(symb_tab, simbolo->lexema, simbolo);
			}else{
				printf(_BOLDGREEN "line %d: " _BOLDRED "error: " _RESET "redeclaration of  ‘"
				_BOLDGREEN "%s"_RESET"’.\n", tokenBackup->linha, tokenBackup->lexema);
			}
		}
		Decl2();
	}else if(tokenEntrada->nome == _PCOMMA){
		casa(_PCOMMA);
	}else if(tokenEntrada->nome == _ATTR){
		casa(_ATTR);
		Expressao();
		Decl2();
	}else{
		//printf("Missing identifier before ->");
	}
}

int Tipo(){
	//printf("TIPO-> "); //remover
	if (tokenEntrada->nome == _INT){
		casa(_INT);
		return _INT;
	}
	else if (tokenEntrada->nome == _FLOAT){
		casa(_FLOAT);
		return _FLOAT;
	}
}

int Comando(){
	//printf("Comando->"); //remover
	if (tokenEntrada->nome == _LBRACE)
		Bloco();
	else if (tokenEntrada->nome == _ID)
		Atribuicao();
	else if (tokenEntrada->nome == _IF)
		ComandoSe();
	else if (tokenEntrada->nome == _WHILE)
		ComandoEnquanto();
	else if (tokenEntrada->nome == _READ)
		ComandoRead();
	else if (tokenEntrada->nome == _PRINT)
		ComandoPrint();
	else if (tokenEntrada->nome == _FOR)
		ComandoFor();
}

int Bloco(){
	//printf("Bloco-> "); //remover
	casa(_LBRACE);
	Decl_Comando();
	casa(_RBRACE);
}

int Atribuicao(){
	//printf("Atribuicao-> "); //remover
	casa(_ID);
	casa(_ATTR);
	Expressao();
	casa(_PCOMMA);
}

int ComandoSe(){
	//printf("ComandoSe-> "); //remover
	casa(_IF);
	casa(_LBRACKET);
	Expressao();
	casa(_RBRACKET);
	Comando();
	ComandoSenao();
}

int ComandoSenao(){
	//printf("ComandoSenao-> "); //remover
	if (tokenEntrada->nome == _ELSE){
		casa(_ELSE);
		Comando();
	}
}

int ComandoEnquanto(){
	//printf("ComandoEnquanto-> "); //remover
	casa(_WHILE);
	casa(_LBRACKET);
	Expressao();
	casa(_RBRACKET);
	Comando();
}

int ComandoRead(){
	//printf("ComandoRead-> "); //remover
	casa(_READ);
	casa(_ID);
	casa(_PCOMMA);
}

int ComandoPrint(){
	//printf("ComandoPrint-> "); //remover
	casa(_PRINT);
	casa(_LBRACKET);
	Expressao();
	casa(_RBRACKET);
	casa(_PCOMMA);
}

int ComandoFor(){
	//printf("ComandoFor-> "); //remover
	casa(_FOR);
	casa(_LBRACKET);
	AtribuicaoFor();
	casa(_PCOMMA);
	Expressao();
	casa(_PCOMMA);
	AtribuicaoFor();
	casa(_RBRACKET);
	Comando();
}

int AtribuicaoFor(){
	//printf("AtribuicaoFor-> "); //remover
	casa(_ID);
	casa(_ATTR);
	Expressao();
}


int Expressao(){
	//printf("Expressao ->"); //remover
	Adicao();
	RelacaoOpc();
}

int RelacaoOpc(){
	if (tokenEntrada->nome == _LT || tokenEntrada->nome == _LE || 
		tokenEntrada->nome == _GT || tokenEntrada->nome == _GE ||
		tokenEntrada->nome == _EQ){
		OpRel();
		Adicao();
		RelacaoOpc();
	}else{}
}

int OpRel(){
	if (tokenEntrada->nome == _LT)
		casa(_LT);
	else if (tokenEntrada->nome == _LE)
		casa(_LE);
	else if (tokenEntrada->nome == _GT)
		casa(_GT);
	else if (tokenEntrada->nome == _GE)
		casa(_GE);
	else if (tokenEntrada->nome == _EQ)
		casa(_EQ);
}

int Adicao(){
	Termo();
	AdicaoOpc();
}

int AdicaoOpc(){
	if (tokenEntrada->nome == _PLUS || tokenEntrada->nome == _MINUS){
		OpAdicao();
		Termo();
		AdicaoOpc();
	}else{}
}

int OpAdicao(){
	if (tokenEntrada->nome == _PLUS)
		casa(_PLUS);
	else if (tokenEntrada->nome == _MINUS)
		casa(_MINUS);
}

int Termo(){
	Fator();
	TermoOpc();
}

int TermoOpc(){
	if (tokenEntrada->nome == _MULT || tokenEntrada->nome == _DIV){
		OpMult();
		Fator();
		TermoOpc();
	}else{}
}

int OpMult(){
	if (tokenEntrada->nome == _MULT)
		casa(_MULT);
	else if (tokenEntrada->nome == _DIV)
		casa(_DIV);
}

int Fator(){
	if (tokenEntrada->nome == _ID)
		casa(_ID);
	else if (tokenEntrada->nome == _INTEGER_CONST)
		casa(_INTEGER_CONST);
	else if (tokenEntrada->nome == _FLOAT_CONST)
		casa(_FLOAT_CONST);
	else if (tokenEntrada->nome == _LBRACKET){
		casa(_LBRACKET);
		Expressao();
		casa(_RBRACKET);
	}
}