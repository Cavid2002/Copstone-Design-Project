#include "src/Networking.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 500



void server_code(ARGUMENTS args)
{
    char buff[BUFF_SIZE];
    int c = recv(args.client_fd, buff, BUFF_SIZE, 0);
    buff[c] = '\0';
    printf("%s", buff);
    exit(0);
}

int main()
{
    SERVER server = create_TCP_server(PORT);
    ARGUMENTS args;
    run_server(server, server_code, args);
}