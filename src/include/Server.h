#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cstring>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

#include "Client.h"
#include "TintinReporter.h"

class Server
{
private:
    int server_fd;
    int epoll_fd;

    TintinReporter reporter;
    std::unordered_map<int, Client> clients;

    void setNonBlocking(int fd)
    {
        int flags = fcntl(fd, F_GETFL, 0);
        if (flags == -1)
        {
            perror("fcntl(F_GETFL)");
            exit(EXIT_FAILURE);
        }
        if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
        {
            perror("fcntl(F_SETFL)");
            exit(EXIT_FAILURE);
        }
    }

public:
    Server(int port) : reporter("matt_daemon.log")
    {
        reporter.LogInfo("Started.");
        reporter.LogInfo("Creating server.");

        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (server_fd == -1)
        {
            reporter.LogError("Error: socket");
            exit(EXIT_FAILURE);
        }

        setNonBlocking(server_fd);

        sockaddr_in server_addr{};
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;
        server_addr.sin_port = htons(port);

        if (bind(server_fd, (sockaddr *)&server_addr, sizeof(server_addr)) == -1)
        {
            reporter.LogError("Error: bind");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        if (listen(server_fd, SOMAXCONN) == -1)
        {
            reporter.LogError("Error: listen");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        epoll_fd = epoll_create1(0);
        if (epoll_fd == -1)
        {
            reporter.LogError("Error: epoll_create");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        epoll_event event{};
        event.events = EPOLLIN;
        event.data.fd = server_fd;

        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event) == -1)
        {
            reporter.LogError("Error: epoll_ctl");
            close(server_fd);
            close(epoll_fd);
            exit(EXIT_FAILURE);
        }

        reporter.LogInfo("Server created.");

        // Deamon Mode
        InitDeamon();
    }
    void run()
    {
        constexpr int MAX_EVENTS = 10;
        epoll_event events[MAX_EVENTS];

        while (true)
        {
            int event_count = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
            if (event_count == -1)
            {
                break;
            }

            for (int i = 0; i < event_count; ++i)
            {
                if (events[i].data.fd == server_fd)
                {
                    acceptClient();
                }
                else
                {
                    handleClient(events[i].data.fd);
                }
            }
        }
    }

private:
    void acceptClient()
    {
        sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_fd = accept(server_fd, (sockaddr *)&client_addr, &client_len);

        if (client_fd == -1)
        {
            return;
        }

        setNonBlocking(client_fd);

        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
        int client_port = ntohs(client_addr.sin_port);

        clients.insert({client_fd, Client(client_fd)});

        epoll_event event{};
        event.events = EPOLLIN | EPOLLET;
        event.data.fd = client_fd;

        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event) == -1)
        {
            close(client_fd);
            clients.erase(client_fd);
            return;
        }

        // std::cout << "New client connected: " << client_ip << ":" << client_port << std::endl;
    }

    void handleClient(int client_fd)
    {
        int bytes_read;
        std::string buffer;
        char c;

        while (true)
        {
            bytes_read = read(client_fd, &c, 1);
            if (bytes_read <= 0)
            {
                if (bytes_read == 0)
                {
                    // handleClientDisconnect(client_fd);
                }

                epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_fd, nullptr);
                close(client_fd);
                clients.erase(client_fd);
                break;
            }
            buffer += c;
        }

        reporter.LogInfo("User input: ", Utility::ClearNewLine(buffer));
    }

    void InitDeamon()
    {
        reporter.LogInfo("Entering Daemon mode.");
    }
};