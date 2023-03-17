/**
 * @file ipkcpc.c
 * @author Matej Keznikl (xkezni01@stud.fit.vutbr.cz)
 * @brief Implementácia klienta pre IPK Calculator Protokol
 * @date 2023-03-21
 */

#include "ipkcpc.h"

int main(int argc, char *argv[])
{
    struct Arguments *arguments = calloc(1, sizeof(struct Arguments));
    arguments->host = calloc(16, sizeof(char));
    arguments->port = calloc(6, sizeof(char));
    arg_check(argc, argv, arguments);

    if (arguments->mode == TCP)
    {
        tcp(arguments);
    }
    else
    {
        udp(arguments);
    }

    free_arguments(arguments);
}