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
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#ifndef HEADER
#define HEADER
#include "header.h"
#endif


void fprintTokens(token_t *tokens, int numTokens, char *arqName){

	FILE *arq = fopen(arqName, "w");
	if (arq == NULL)
		printf("Could not open output file\n");
	fprintf(arq,"-------Token Buffer------------\n"
			"Token          | Num. da Linha | Lexema\n"
			"-----------------------------------------------\n");
	token_t tkn;
	for (int i = 0; i < numTokens; i++){
		fprintf(arq,"%-15s  %-15d %-7s\n", numToToken(tokens[i].nome), tokens[i].linha, tokens[i].lexema);
	}
	fclose(arq);
}

int isValidFile(char *file){
	if (file[strlen(file)-2] == '.' && file[strlen(file)-1] == 'c')
		return 1;
	printf("Invalid file format!\n");
	return 0;
}

void compilaArquivo(char *inputFileName){
	FILE *fonte = fopen(inputFileName, "r");
	char *outputFileName = (char*) malloc (50*sizeof(char));
	int i;
	if (fonte == NULL){
		printf("Arquivo não encontrado!\n");
		return;
	}
	if (!isValidFile(inputFileName)){
		return;
	}

	for (i = 0; inputFileName[i] != '.'; i++){
		outputFileName[i] = inputFileName[i];
	}
	outputFileName[i] = '\0';
	strcat(outputFileName, ".txt");
	

	int numTokens;
	token_t* tokens = analisadorLexico(fonte, &(numTokens));
	fprintTokens(tokens, numTokens, outputFileName);
	inputFileName[0] = '\0';
	printf("analisado\n");

	
	analisadorSintatico(tokens, numTokens);
	fclose(fonte);	 
}

void compilaDiretorio(char *dir){
	struct dirent *de;

	int i;
	char* inputFileName = (char*) malloc(50*sizeof(char));
	char *outputFileName= (char*) malloc(50*sizeof(char));

	DIR *dr = opendir(dir); 
	FILE *fonte;
	if (dr == NULL){  // opendir returns NULL if couldn't open directory 
		printf("Could not open current directory\n" ); 
	}

	int numTokens;
	token_t *tokens;
		

	while ((de = readdir(dr)) != NULL){
		strcpy(inputFileName, dir);
		strcat(inputFileName, "/");
		printf("%s\n", de->d_name);
		if (de->d_name[0] == '.')
			continue;

		strcat(inputFileName, de->d_name);
		
		if (!isValidFile(inputFileName))
			return;

		fonte = fopen(inputFileName,"r");
		for (i = 0; de->d_name[i] != '.'; i++){
			outputFileName[i] = inputFileName[i];
		}
		outputFileName[i] = '\0';
		strcat(outputFileName, ".txt");
		
		if (fonte == NULL){							
			printf("Arquivo %s não encontrado.\n", inputFileName);
			continue;
		}
			
		tokens = analisadorLexico(fonte, &(numTokens));
		fprintTokens(tokens, numTokens, outputFileName);
		inputFileName[0] = '\0';
		printf("analisado\n");
		analisadorSintatico(tokens, numTokens);
		printf("COMPILADO\n\n\n\n");

	}
	closedir(dr);	 

}


int main (int argc, char* argv[]){
	if (argc < 2){
		printf("\nusage: ./main file_or_folder\n");
		return 0;
	}
	FILE *arq = fopen(argv[1], "r");

	DIR *dr = opendir(argv[1]);

	if (dr == NULL){			//se nao é pasta
		if (arq == NULL){		//se nao é arquivo
			printf("%s nao encontrado.\n", argv[1]);
			return 0;
		}else{
			fclose(arq);
			compilaArquivo(argv[1]); 
		}
	}else{
		compilaDiretorio(argv[1]);
		closedir(dr);	 

	}
	return 0;
}
