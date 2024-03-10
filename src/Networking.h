#include <sys/socket.h>
#include <arpa/inet.h>

#define Q_SIZE 1
#define PORT 2000

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr; 
typedef int socket_d;

typedef struct{
    socket_d fd;
    unsigned int addr_fam;
    unsigned int type;
    unsigned short port;
    unsigned int q_size;
} SERVER;

typedef struct{
    sockaddr_in client_data;
    socket_d client_fd;
    void* args;
} ARGUMENTS;

socket_d create_socket(unsigned int addr_family, unsigned int type);

void bind_to_port(socket_d fd, unsigned int addr_family ,unsigned short port);

void start_listening(socket_d fd, int q_size);

socket_d accept_connection(socket_d fd, sockaddr_in* client);

void connect_to_addr(socket_d fd, const char* ip_addr, unsigned short port, unsigned int addr_family);

SERVER create_TCP_server(unsigned short port);

void run_server(SERVER server, void (*func)(ARGUMENTS), ARGUMENTS args);
