#Makefile
#Riešenie IPK-projekt č.1
#Datum odovzdania: 13.3.2023
#Autor: Matej Keznikl
#Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
#Prelozene: GCC 11.3.0
#Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
#Popis: Makefile pre IPK-projekt č.1

CC = gcc
CFLAGS = -g -std=c18 -pedantic -Wall -Wextra 

.PHONY: build clean

build:
	$(CC) $(CFLAGS) -c ipkcpc.c -o ipkcpc

zip:
	zip xkezni01 *
clean:
	rm -f ipkcpc
	rm -f xkezni01.zip
	rm -f *.o 