/**
 * @file udp.h
 * @author Matej Keznikl (xkezni01@stud.fit.vutbr.cz)
 * @brief Hlavičkové súbory pre UDP komunikáciu klienta pre IPK Calculator Protokol
 * @date 2023-03-21
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "args.h"

#define BUFSIZE 512
#define OPCODE_POSITION 0
#define STATUS 1 
#define RECIEVE_PAYLOAD 2
#define SEND_PAYLOAD 1

#define REQUEST 0
#define RESPONSE 1

#define OK 0 
#define ERROR 1

#define OPCODE 1
#define PAYLOAD 1
#define LINEFEED 1

#define PAYLOAD_LENGTH_MAX 255

extern void null_memory(char *memory, int memory_size);

/**
 * @brief Vykoná UDP komunikáciu pre zadané argumenty programu
 *
 * @param args Skontrolované argumenty programu
 */
void udp(struct Arguments *args);