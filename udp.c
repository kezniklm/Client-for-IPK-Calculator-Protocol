/**
 * @file udp.c
 * @author Matej Keznikl (xkezni01@stud.fit.vutbr.cz)
 * @brief Funkcie pre UDP komunikáciu klienta pre IPK Calculator Protokol
 * @date 2023-03-21
 */

#include "udp.h"

/**
 * @brief Vykoná UDP komunikáciu pre zadané argumenty programu
 *
 * @param args Skontrolované argumenty programu
 */
void udp(struct Arguments *args)
{
	int client_socket, port_number, bytestx, bytesrx;
	socklen_t serverlen;
	const char *server_hostname;
	struct hostent *server;
	struct sockaddr_in server_address;
	struct pollfd pfd[1];

	char buf[BUFSIZE];
	char help_buf[BUFSIZE];
	char temp[BUFSIZE];
	int buf_length = 0;

	/* Načítanie spracovaného vstupu */
	server_hostname = args->host;
	char *text;
	port_number = strtol(args->port, &text, 10);

	if ((server = gethostbyname(server_hostname)) == NULL)
	{
		error_exit("Zadaný host neexistuje %s", server_hostname);
	}

	null_memory((char *)&server_address, sizeof(server_address));
	server_address.sin_family = AF_INET;
	memcpy((char *)&server_address.sin_addr.s_addr, (char *)server->h_addr_list[0], server->h_length);
	server_address.sin_port = htons(port_number);

	/* Vytvorenie socketu */
	if ((client_socket = socket(AF_INET, SOCK_DGRAM, 0)) <= 0)
	{
		perror("ERROR: socket");
		exit(EXIT_FAILURE);
	}

	/* Komunikácia so serverom */
	while (true)
	{
		null_memory(buf, BUFSIZE);
		null_memory(help_buf, BUFSIZE);
		null_memory(temp, BUFSIZE);

		/* Načítanie vstupu od užívateľa */
		if (!fgets(temp, BUFSIZE, stdin) || !strchr(temp, '\n'))
		{
			error_exit("Zadaný vstupný text sa nepodarilo načítať");
		}

		/* Spracovanie vstupu tak aby bol WELL-FORMED */
		strcpy(buf, "0");
		buf_length = strlen(temp) - LINEFEED + OPCODE + PAYLOAD;
		if ((strlen(temp) - LINEFEED) > PAYLOAD_LENGTH_MAX)
		{
			error_exit("Zadaný vstupný text je dlhší ako maximálny povolený počet znakov");
		}
		help_buf[0] = '\0' + strlen(temp) - LINEFEED;
		strcat(buf, help_buf);
		strcat(buf, temp);
		buf[0] = '\0';
		buf[strcspn(buf, "\n")] = 0;

		/* Odoslanie správy od užívateľa na server */
		serverlen = sizeof(server_address);
		bytestx = sendto(client_socket, buf, buf_length, 0, (struct sockaddr *)&server_address, serverlen);
		if (bytestx < 0)
		{
			perror("ERROR: sendto");
		}

		pfd[0].fd = client_socket;
		pfd[0].events = POLLIN;

		int n = poll(pfd, 1, ALLOWED_TIMEOUT * 1000);

		if (n == 0)
		{
			warning_msg("Timeout\n");
			continue;
		}
		else if (n < 0)
		{
			error_exit("%s\n", strerror(errno));
		}
		null_memory(buf, BUFSIZE);
		null_memory(help_buf, BUFSIZE);
		null_memory(temp, BUFSIZE);

		/* Prijatie správy od servera */
		bytesrx = recvfrom(client_socket, buf, BUFSIZE, 0, (struct sockaddr *)&server_address, &serverlen);
		if (bytesrx < 0)
		{
			perror("ERROR: recvfrom");
		}
		if (buf[OPCODE_POSITION] == RESPONSE)
		{
			if (buf[STATUS] == OK)
			{
				strncpy(help_buf, buf + OPCODE + STATUS + PAYLOAD, sizeof(help_buf) - OPCODE - STATUS - PAYLOAD);
				printf("OK:%s\n", help_buf);
			}
			else if (buf[STATUS] == ERROR)
			{
				strncpy(help_buf, buf + OPCODE + STATUS + PAYLOAD, sizeof(help_buf) - OPCODE - STATUS - PAYLOAD);
				printf("ERR:%s\n", help_buf);
			}
			else
			{
				error_exit("Neočakávaný response kód\n");
			}
		}
		buf_length = 0;
	}
}
