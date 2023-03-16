/**
 * @file args.h
 * @author Matej Keznikl (xkezni01@stud.fit.vutbr.cz)
 * @brief Funkcie pre spracovanie argumentov programu ipkcpc
 * @date 2023-03-21
 */

#include "args.h"

/**
 * @brief Skontroluje octety IPV4 adresy aby boli v intervale <0,255>
 * 
 * @param octet 
 * @param octet_num 
 */
void check_scope(char *octet, int *octet_num)
{
    if (!octet)
    {
        error_exit("IP adresa nemá požadovaný formát\n");
    }
    char *tmp;
    int int_octet = strtol(octet, &tmp, 10);
    if (strcmp(tmp,"") != 0 || int_octet < 0 || int_octet > 255)
    {
        error_exit("IP adresa nemá požadovaný formát\n");
    }
    (*octet_num)++;
}

/**
 * @brief Skontroluje formát zadanej IPV4 adresy
 * 
 * @param ip_adress 
 */
void check_ip_format(char *ip_adress)
{
    if (!ip_adress || strlen(ip_adress) > IP_LENGTH)
    {
        error_exit("IP adresa nemá požadovaný formát\n");
    }

    char *octet = strtok(ip_adress, ".");
    int octet_number = 0;
    check_scope(octet, &octet_number);
    while (octet)
    {
        if (octet_number > IP_OCTETS)
        {
            error_exit("IP adresa nemá požadovaný formát\n");
        }
        check_scope(octet, &octet_number);
        octet = strtok(NULL, ".");
    }
}

/**
 * @brief Skontroluje formát zadaného portu
 * 
 * @param port 
 */
void check_port_format(char *port)
{
    if (!port || strlen(port) > MAX_PORT_LENGTH)
    {
        error_exit("Port nemá požadovaný formát\n");
    }
    char *tmp;
    int int_port = strtol(port, &tmp, 10);

    if (strcmp(tmp,"") != 0 || int_port < 0 || int_port > MAX_PORT)
    {
       error_exit("Port nemá požadovaný formát\n"); 
    }
}

/**
 * @brief Skontroluje a spracuje argumenty programu ipkcpc
 * 
 * @param argc Počet argumentov
 * @param argv Argumenty programu
 * @param args Štruktúra na uloženie spracovaných argumentov
 */
void arg_check(int argc, char *argv[], struct Arguments *args)
{
    if (argc != ARGUMENTS_NUMBER)
    {
        error_exit("Nesprávny počet argumentov programu\n");
    }
    for (int argument = FIRST_ARGUMENT; argument < ARGUMENTS_NUMBER; argument++)
    {
        if (!strcmp(argv[argument], "-h"))
        {
            if(argv[argument + 1] != NULL)
            {
                strncpy(args->host,argv[argument + 1],IP_LENGTH + ENDING_ZERO);
            }
            check_ip_format(argv[argument + 1]);
            argument++;
        }
        else if (!strcmp(argv[argument], "-p"))
        {
            if(argv[argument + 1] != NULL)
            {
                strncpy(args->port,argv[argument + 1],MAX_PORT_LENGTH + ENDING_ZERO);
            }
            check_port_format(argv[argument + 1]);
            argument++;
        }
        else if (!strcmp(argv[argument], "-m"))
        {
            if (!strcmp(argv[argument + 1], "tcp"))
            {
                args->mode = TCP;
            }
            else if (!strcmp(argv[argument + 1], "udp"))
            {
                args->mode = UDP;  
            }
            else
            {
                error_exit("Nesprávny mód pri zadávaní argumentov programu\n");
            }
            argument++;
        }
        else
        {
            error_exit("Nesprávny argument zadaný pri zadávaní argumentov programu\n");
        }
    }
}

/**
 * @brief Uvoľní pamäť alokovanú štruktúrou Arguments
 * 
 * @param args 
 */
void free_arguments(struct Arguments *args)
{
    free(args->host);
    free(args->port);
    free(args);
}

