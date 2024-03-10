#include "src/Networking.h"
#include <stdio.h>

int main()
{
    SERVER server = create_TCP_server(2000);
    run_server(server);
}