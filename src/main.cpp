#include "include/utility/utility.h"
#include "include/Server.h"

#include <iostream>

int main()
{
    Logger logger("matt_daemon.log2");
    logger.logLevel("Hello, World!", "asda");

    Server server(8080);
    server.run();

    return 0;
}