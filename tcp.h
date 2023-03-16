/**
 * @file tcp.h
 * @author Matej Keznikl (xkezni01@stud.fit.vutbr.cz)
 * @brief Hlavičkové súbory pre TCP komunikáciu klienta pre IPK Calculator Protokol
 * @date 2023-03-21
 */

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <signal.h>

#include "args.h"

#define BUFSIZE 1024

/**
 * @brief Vykoná TCP komunikáciu pre zadané argumenty programu 
 *
 * @param args Skontrolované argumenty programu
 */
void tcp(struct Arguments *args);

/**
 * @brief Vynuluje pamäť zadanú ako argument funkcie o zadanej veľkosti
 *
 * @param memory Pamäť na vynulovanie
 * @param memory_size Veľkosť pamäti na vynulovanie
 */
void null_memory(char *memory, int memory_size);
