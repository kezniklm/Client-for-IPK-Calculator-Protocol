/**
 * @file ipkcpc.c
 * @author Matej Keznikl (xkezni01@stud.fit.vutbr.cz)
 * @brief Implementácia klienta pre IPK Calculator Protokol
 * @date 2023-03-21
 */

#include "ipkcpc.h"

void free_memory(struct Arguments *args)
{
    free(args);
}

/**
 * @brief 
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
 * @brief 
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
 * @brief 
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
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @param args 
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
            check_ip_format(argv[argument + 1]);
            args->host = argv[argument + 1];
            argument++;
        }
        else if (!strcmp(argv[argument], "-p"))
        {
            check_port_format(argv[argument + 1]);
            args->port = argv[argument + 1];
            argument++;
        }
        else if (!strcmp(argv[argument], "-m"))
        {
            if (strcmp(argv[argument + 1], "tcp") != 0 && strcmp(argv[argument + 1], "udp") != 0)
            {
                error_exit("Nesprávny mód pri zadávaní argumentov programu\n");
            }
            args->port = argv[argument + 1];
            argument++;
        }
        else
        {
            error_exit("Nesprávny argument zadaný pri zadávaní argumentov programu\n");
        }
    }
}

int main(int argc, char *argv[])
{
    struct Arguments *arguments = calloc(1, sizeof(struct Arguments));
    arg_check(argc, argv, arguments);
    free_memory(arguments);
}