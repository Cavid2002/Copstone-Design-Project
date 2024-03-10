#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#include <unistd.h>
#include <fcntl.h>
#include "Networking.h"



void error(const char* msg)
{
    fprintf(stderr, "[ERROR] %s!\n", msg);
    exit(EXIT_FAILURE);
}

socket_d create_socket(unsigned int addr_family, unsigned int type)
{
    socket_d fd = socket(addr_family, type, 0);
    if(fd == -1)
    {
        error("Unable to create new socket!");
    }
    return fd;
}

void bind_to_port(socket_d fd, unsigned int addr_family ,unsigned short port)
{
    sockaddr_in name;
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    name.sin_family = addr_family;
    name.sin_port = htons(port);
    
    int reuse = 1;
    if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
    {
        error("Unable to reuse the port");   
    }

    if(bind(fd, (sockaddr*)&name, sizeof(name)) == -1)
    {
        error("Unable to bind to specified port");
    }

    return;
}

void start_listening(socket_d fd, int queue_size)
{
    if(listen(fd, queue_size) == -1)
    {
        error("Unable to listen");
    }
    return;
}

socket_d accept_connection(socket_d fd, sockaddr_in* client)
{
    socklen_t client_size = sizeof(client);
    socket_d client_fd = accept(fd, (sockaddr*)&client, &client_size);

    if(client_fd == -1)
    {
        error("Unable to accept the connection");
    }

    return client_fd;
}

void connect_to_addr(socket_d fd, const char* ip_addr, unsigned short port, unsigned int addr_family)
{
    sockaddr_in name;
    name.sin_addr.s_addr = inet_addr(ip_addr);
    name.sin_family = addr_family;
    name.sin_port = htons(port);
    
    if(connect(fd, (sockaddr*)&name, sizeof(name)) == -1)
    {
        error("Unable to connect");
    }

    return;
}

SERVER create_TCP_server(unsigned short port)
{
    SERVER server;
    server.addr_fam = AF_INET;
    server.q_size = Q_SIZE;
    server.port = port;
    server.type = SOCK_STREAM;
    
    return server;
}

void run_server(SERVER server, void (*func)(ARGUMENTS args), ARGUMENTS args)
{
    server.fd = create_socket(server.addr_fam, server.type);
    bind_to_port(server.fd, server.addr_fam, server.port);
    start_listening(server.fd, server.q_size);
    fprintf(stdout, "[INFO]Server is listening on port: %d\n", server.port);
    while(true)
    {
        sockaddr_in client_data;
        socket_d client_fd = accept_connection(server.fd, &client_data);
        
        args.client_data = client_data;
        args.client_fd = client_fd;
        func(args);

        close(client_fd);
    }
}


