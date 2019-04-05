all:
	gcc -c src/main.c src/IO.c src/analisadorLexico.c src/analisadorSintatico.c src/tokens.c src/hash.c
	gcc main.o IO.o analisadorLexico.o analisadorSintatico.o tokens.o hash.o -o main
	rm *.o

ddd:
	gcc -g -c src/main.c
	gcc -g -c src/IO.c
	gcc -g -c src/analisadorLexico.c
	gcc -g -c src/tokens.c
	gcc -g -c src/analisadorSintatico.c 
	gcc -g -c src/hash.c 
	gcc -g main.o IO.o analisadorLexico.o analisadorSintatico.o tokens.o hash.o -o main
	rm *.o
	ddd main

clean: 
	rm main