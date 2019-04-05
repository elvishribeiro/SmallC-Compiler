//tokens.c

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
 
#include "header.h"

char* numToToken(int num){
	if (num == _PCOMMA)
		return "PCOMMA";
	if (num == _COMMA)
		return "COMMA";
	if (num == _LBRACKET)
		return "LBRACKET";
	if (num == _RBRACKET)
		return "RBRACKET";
	if (num == _LBRACE)
		return "LBRACE";
	if (num == _RBRACE)
		return "RBRACE";
	if (num == _ATTR)
		return "ATTR";
	if (num == _PLUS)
		return "PLUS";
	if (num == _MINUS)
		return "MINUS";
	if (num == _MULT)
		return "MULT";
	if (num == _DIV)
		return "DIV";
	if (num == _LCOL)
		return "LCOL";
	if (num == _RCOL)
		return "RCOL";
	if (num == _INTEGER_CONST)
		return "INTEGER_CONST";
	if (num == _FLOAT_CONST)
		return "FLOAT_CONST";
	if (num == _EQ)
		return "EQ";
	if (num == _LT)
		return "LT";
	if (num == _LE)
		return "LE";
	if (num == _GT)
		return "GT";
	if (num == _GE)
		return "GE";
	if (num == _ID)
		return "ID";
	if (num == _MAIN)
		return "MAIN";
	if (num == _INT)
		return "INT";
	if (num == _FLOAT)
		return "FLOAT";
	if (num == _IF)
		return "IF";
	if (num == _ELSE)
		return "ELSE";
	if (num == _WHILE)
		return "WHILE";
	if (num == _FOR)
		return "FOR";
	if (num == _READ)
		return "READ";
	if (num == _PRINT)
		return "PRINT";
	return "";
}
