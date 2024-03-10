#include "src/Networking.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 500



void server_code(Client cli)
{
    char buff[BUFF_SIZE];
    int c = recv(cli.fd, buff, BUFF_SIZE, 0);
    buff[c] = '\0';
    printf("%s\n", buff);
    exit(0);
}

int main()
{
    SERVER server = create_TCP_server(PORT);
    run_server(server, server_code);
}