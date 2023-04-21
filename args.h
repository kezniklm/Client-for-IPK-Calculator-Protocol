/**
 * @file args.h
 * @author Matej Keznikl (xkezni01@stud.fit.vutbr.cz)
 * @brief Hlavičkový súbor pre spracovanie argumentov programu ipkcpc
 * @date 2023-03-21
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "error.h"

#define ARGUMENTS_NUMBER 7
#define FIRST_ARGUMENT 1
#define IP_LENGTH 15
#define IP_OCTETS 4
#define MAX_PORT_LENGTH 5
#define MAX_PORT 65535
#define UDP false
#define TCP true
#define ENDING_ZERO 1

/**
 * @brief Štruktúra spracovaných argumentov obsahujúca IP adresu hosta, port a mód (TCP/UDP)
 */
struct Arguments
{
    char *host;
    char *port;
    bool mode;
};

/**
 * @brief Skontroluje a spracuje argumenty programu ipkcpc
 *
 * @param argc Počet argumentov
 * @param argv Argumenty programu
 * @param args Štruktúra na uloženie spracovaných argumentov
 */
void arg_check(int argc, char *argv[], struct Arguments *args);

/**
 * @brief Skontroluje formát zadaného portu
 *
 * @param port
 */
void check_port_format(char *port);

/**
 * @brief Skontroluje formát zadanej IPV4 adresy
 *
 * @param ip_adress
 */
void check_ip_format(char *ip_adress);

/**
 * @brief Skontroluje octety IPV4 adresy aby boli v intervale <0,255>
 *
 * @param octet
 * @param octet_num
 */
void check_scope(char *octet, int *octet_num);

/**
 * @brief Uvoľní pamäť alokovanú štruktúrou Arguments
 *
 * @param args
 */
void free_arguments(struct Arguments *args);
