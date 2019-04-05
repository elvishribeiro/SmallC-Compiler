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

#define BUFFSIZE 100

char buffer[BUFFSIZE];
int buf_cont = -1;

int fillBuffer(FILE *arq){
	buf_cont = 0;
	fgets(buffer, 100, arq);
}

char getNextChar(FILE *arq){
	if (buffer[buf_cont] == '\0' || buf_cont == -1){
		if (!fillBuffer(arq)){
			return '\0';
		}
	}
	return buffer[buf_cont++];
}

void resetBuff(){
	buf_cont = -1;
}