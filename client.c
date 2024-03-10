#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "src/Networking.h"

const char* msg = "CONNECTION ESTABLISHED!";

int main()
{  
    socket_d fd = create_socket(AF_INET, SOCK_STREAM);
    connect_to_addr(fd, "127.0.0.1", PORT, AF_INET);
    send(fd, msg, strlen(msg), 0);
    close(fd);
    return 0;
}