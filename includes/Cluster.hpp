#ifndef CLUSTER_HPP
#define CLUSTER_HPP

#include "Server.hpp"
#include "ConfigurationParser.hpp"

class Cluster {
public:
    Cluster(ClusterConfiguration& config);
    ~Cluster();
    void run();

private:
    int epoll_fd;
    ClusterConfiguration config;
    std::vector<Server*> servers;
    std::map<int, int> client_to_server;
    std::map<int, Server*> server_fd_to_server; // Add this line

    void createEpoll();
    void addSocketToEpoll(int fd);
    void handleEvents(struct epoll_event* events, int numEvents);
    void acceptConnections(int serverSocket);
    void handleClient(int client_fd);
    void serveErrorPage(int client_fd, const std::string& error_code, Server* server);
    bool isServerFd(int fd);
    void cleanup();
};

#endif // CLUSTER_HPP