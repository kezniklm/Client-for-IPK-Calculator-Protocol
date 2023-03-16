#Makefile
#Riešenie IPK-projekt č.1
#Datum odovzdania: 13.3.2023
#Autor: Matej Keznikl
#Fakulta: Fakulta informačných technológií VUT v Brne (FIT VUT)
#Prelozene: GCC 11.3.0
#Testované na zariadeniach s operačnými systémami: Ubuntu 20.04, Debian 10, Cent OS 7,...
#Popis: Makefile pre IPK-projekt č.1

CC = gcc
CFLAGS = -std=c18 -pedantic -Wall -Wextra -Werror -g -fcommon 

.PHONY: error.o args.o tcp.o udp.o ipkcpc.o ipkcpc zip clean

ipkcpc: error.o args.o tcp.o udp.o ipkcpc.o
	$(CC) $(CFLAGS) error.o args.o tcp.o ipkcpc.o -o ipkcpc

error.o: error.h error.c 
	$(CC) $(CFLAGS) -c error.c -o error.o

args.o: args.h args.c
	$(CC) $(CFLAGS) -c args.c -o args.o

tcp.o: tcp.h tcp.c
	$(CC) $(CFLAGS) -c tcp.c -o tcp.o

udp.o:udp.h udp.c
	$(CC) $(CFLAGS) -c udp.c -o udp.o
	
ipkcpc.o: ipkcpc.h
	$(CC) $(CFLAGS) -c ipkcpc.c -o ipkcpc.o

zip:
	zip xkezni01 *
	
clean:
	rm -f ipkcpc
	rm -f xkezni01.zip
	rm -f *.o 