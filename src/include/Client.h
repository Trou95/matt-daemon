#include <string>

class Client
{
public:
    const int fd;

    Client() = default;
    Client(int client_fd)
        : fd(client_fd) {};
};