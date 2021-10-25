

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99


build: star_dust
	./star_dust

tema2: tema2.c
	$(CC) $(CFLAGS) star_dust.c -o star_dust

pack:
	zip -FSr 315CA_BiancaNecula_Tema2.zip README Makefile *.c *.h

clean:
	rm -f star_dust

