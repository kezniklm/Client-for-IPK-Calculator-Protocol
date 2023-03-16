/**
 * @file tcp.c
 * @author Matej Keznikl (xkezni01@stud.fit.vutbr.cz)
 * @brief Funkcie pre TCP komunikáciu klienta pre IPK Calculator Protokol
 * @date 2023-03-21
 */

#include "tcp.h"

/**
 * @brief Vynuluje pamäť zadanú ako argument funkcie o zadanej veľkosti
 *
 * @param memory Pamäť na vynulovanie
 * @param memory_size Veľkosť pamäti na vynulovanie
 */
void null_memory(char *memory, int memory_size)
{
	memset(memory, '\0', memory_size);
}

/**
 * @brief Vykoná TCP komunikáciu pre zadané argumenty programu 
 *
 * @param args Skontrolované argumenty programu
 */
void tcp(struct Arguments *args)
{
	int client_socket, port_number, bytestx, bytesrx;
	socklen_t serverlen;
	const char *server_hostname;
	struct hostent *server;
	struct sockaddr_in server_address;
	char buf[BUFSIZE];

	server_hostname = args->host;
	char *text;
	port_number = strtol(args->port, &text, 10);

	null_memory((char *)&server_address, sizeof(server_address));

	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(port_number);

	/* Vytvorenie socketu */
	if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) <= 0)
	{
		perror("ERROR: socket");
		exit(EXIT_FAILURE);
	}

	/* Nadviazanie spojenia so serverom */
	if (connect(client_socket, (const struct sockaddr *)&server_address, sizeof(server_address)) != 0)
	{
		perror("ERROR: connect");
		exit(EXIT_FAILURE);
	}

	/* Komunikácia so serverom */
	while (true)
	{
		if (!strcmp(buf, "BYE\n"))
		{
			break;
		}

		null_memory(buf, BUFSIZE);

		/* Načítanie vstupu od užívateľa */
		if (!fgets(buf, BUFSIZE, stdin) || !strchr(buf, '\n'))
		{
			/* Ošetrenie v prípade, že riadok zo vstupu je dlhší ako veľkost bufferu */
			null_memory(buf, BUFSIZE);
			strcpy(buf, "BYE\n");
			printf("%s", buf);
			bytestx = send(client_socket, buf, strlen(buf), 0);
			if (bytestx < 0)
			{
				perror("ERROR in sendto");
			}

			null_memory(buf, BUFSIZE);
			bytesrx = recv(client_socket, buf, BUFSIZE, 0);

			if (bytesrx < 0)
			{
				perror("ERROR in recvfrom");
			}
			printf("%s", buf);

			close(client_socket);
			error_exit("Zadaný vstupný text sa nepodarilo načítať");
		}

		/* Odoslanie správy od užívateľa na server */
		bytestx = send(client_socket, buf, strlen(buf), 0);
		if (bytestx < 0)
		{
			perror("ERROR in sendto");
		}

		null_memory(buf, BUFSIZE);
	
		/* Prijatie správy od servera */
		bytesrx = recv(client_socket, buf, BUFSIZE, 0);

		if (bytesrx < 0)
		{
			perror("ERROR in recvfrom");
		}
		printf("%s", buf);

		/* V prípade obdržania správy "BYE\n" od servera ukončenie komunikácie */
		if (!strcmp(buf, "BYE\n"))
		{
			break;
		}
	}
	
	close(client_socket);
}