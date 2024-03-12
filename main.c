#include "src/Networking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFF_SIZE 500

char buff[BUFF_SIZE];


void server_code(Client cli)
{
    memset(buff, 0, BUFF_SIZE);
    int c = recv(cli.fd, buff, BUFF_SIZE, 0);
    buff[c] = '\0';
    printf("%s\n", buff);
    while(true)
    {  
        fprintf(stdout, "[INFO]ENTER COMMAND:");
        fgets(buff, BUFF_SIZE, stdin);

        buff[strlen(buff) - 1] = '\0';
        
        send(cli.fd, buff, strlen(buff), 0);
        c = recv(cli.fd, buff, BUFF_SIZE, 0);
        fprintf(stdout, "%s\n", buff);
    }
    
    
    exit(0);
}

int main()
{
    SERVER server = create_TCP_server(PORT);
    run_server(server, server_code);
}