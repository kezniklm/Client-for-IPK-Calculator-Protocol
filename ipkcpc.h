/**
 * @file ipkcpc.h
 * @author Matej Keznikl (xkezni01@stud.fit.vutbr.cz)
 * @brief Implementácia klienta pre IPK Calculator Protokol
 * @date 2023-03-21
 */

#include <stdlib.h>     
#include <stdio.h>
#include <string.h>

#include "error.h"

#define ARGUMENTS_NUMBER 7
#define FIRST_ARGUMENT 1
#define IP_LENGTH 15
#define IP_OCTETS 4
#define MAX_PORT_LENGTH 5
#define MAX_PORT 65535

struct Arguments{
    char *host;
    char *port;
    char* mode;
};

void arg_check(int argc, char *argv[], struct Arguments *args);

void check_port_format(char *port);

void check_ip_format(char *ip_adress);

void check_scope(char *octet, int *octet_num);