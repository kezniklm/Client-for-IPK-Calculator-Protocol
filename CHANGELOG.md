# IPK projekt 1
## Autor 
[Matej Keznikl ( xkezni01 )](https://github.com/kezniklm/)

## Implementácia 
Projekt je implementovaný v jazyku C, revízia C18 (ISO/IEC 9899:2018). Doporučuje sa prekladač **gcc verzie 7.5.0** a jeho novšie vydania.

V rámci projektu bol implementovaný klient pre IPK Calculator Protokol (IPKCP), ktorý komunikuje pomocou TCP alebo UDP protokolu so servermi používajúcimi protokol IPKCP. 

## Limitácie
* Maximálna dĺžka načítaného vstupu
    * V móde TCP je možné načítať maximálne 1024 znakov zo vstupu pomocou funkcie fgets(). Táto limitácia by sa dala ľahko napraviť použítím funkcie getline(), ktorá si sama alokuje pamäť, ale bolo by to rizikové voči útokom - umožňuje alokovať na 100GB pamäte na zariadení, kde je napr. iba 4GB pamäte, pričom hrozí pád operačného systému.
    * V móde UDP je možné načítať maximálne 255 znakov zo vstupu, pretože Payload length je 8 bitov -> maximálne 255 znakov
