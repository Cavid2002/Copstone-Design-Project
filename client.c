#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

#include "src/Networking.h"
#include "src/StrManip.h"

#define BUFF_SIZE 1024

const char* msg = "CONNECTION ESTABLISHED!";
char buff[BUFF_SIZE];


void client_code(socket_d fd)
{
    send(fd, msg, strlen(msg), 0);
    int c;
    while(true)
    {
        c = recv(fd, buff, BUFF_SIZE, 0);
        buff[c] = '\0';
        char** tokens = split_str(buff, ' ');

        int pipes[2];
        fcntl(pipes[0], F_SETFL, O_NONBLOCK);
        pipe(pipes);


        pid_t id = fork();
        if(id == 0)
        {
            close(pipes[0]);
            dup2(pipes[1], STDOUT_FILENO);
            
            execv(tokens[0], tokens);

            exit(EXIT_SUCCESS);   
        }
        close(pipes[1]);

        c = read(pipes[0], buff, BUFF_SIZE);
        if(c == 0)
        {
            close(pipes[0]);
            continue;
        }
        buff[c] = '\0';

        send(fd, buff, c, 0);
        close(pipes[0]);
    }
    
    
}

int main()
{  
    socket_d fd = create_socket(AF_INET, SOCK_STREAM);
    connect_to_addr(fd, "127.0.0.1", PORT, AF_INET);
    client_code(fd);
    close(fd);
    return 0;
}