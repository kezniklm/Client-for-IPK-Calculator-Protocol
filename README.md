# IPK projekt 1
## Autor
[Matej Keznikl ( xkezni01 )](https://github.com/kezniklm/)
## Zadanie
Cieľom projektu bolo vytvoriť klienta pre IPK Calculator Protokol (IPKCP), ktorý komunikuje pomocou TCP alebo UDP protokolu so servermi používajúcimi protokol IPKCP.

## Implementácia 

Projekt je implementovaný v jazyku C, revízia C18 (ISO/IEC 9899:2018). Doporučuje sa prekladač **gcc verzie 7.5.0** a jeho novšie vydania.

## Použité knižnice potrebné k prekladu

* stdio.h
* stdlib.h
* string.h
* stdbool.h
* stdarg.h
* sys/socket.h
* sys/types.h
* netdb.h
* arpa/inet.h
* netinet/in.h
* unistd.h
* signal.h

## Preklad 
Preloženie projektu je možné programom GNU Make, zadaním príkazu **```make```**, pričom je nutné pred preložením projektu **```rozbaliť```** zip archív.

```
$ unzip xkezni01.zip
$ make
```

## Spustenie
Projekt je spúšťaný z príkazovej riadky, pričom prepínače je možné vzájomne zameniť.
```
$ ./ipkcpc -h <host> -p <port> -m <mode>
    -h <host>
        IPv4 adresa - identifikácia serveru ako koncového bodu komunikácie klienta
    -p <port>
        Cieľové číslo portu, ktoré musí byť v intervale <0,65535>
    -m <mode>
        Protokol používaný pre komunikáciu so serverom
```
## Príklady spustenia
```
$ ./ipkcpc -h 127.0.0.1 -p 2023 -m tcp

$ ./ipkcpc -p 65000 -m udp -h 192.168.100.1

$ ./ipkcpc -m udp -h 192.168.100.1 -p 65000
```
