#include "sockserver.hpp"
#include <arpa/inet.h>
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <unistd.h>
#include <iostream>
int SockServer::Create()
{
    /**
     * Create socket with 
     * Domain: integer, communication domain e.g., AF_INET (IPv4 protocol) , AF_INET6 (IPv6 protocol)
     * type: communication type
     *  SOCK_STREAM: TCP(reliable, connection oriented)
     *  SOCK_DGRAM: UDP(unreliable, connectionless)
     * 0 : Protocol value for Internet Protocol(IP)
    */
    if ((_fd_session = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        return -1; 
    }
    return 0;   
}

int SockServer::Setup()
{
    int opt = 1;
    int ret = 0;
    /**
     * add options for socket referred by file descriptor
     * SO_REUSEADDR, SO_REUSEPORT : reuse of address and port when other connnection come
    */
    if ((ret = setsockopt(_fd_session, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) != 0)
    { 
        perror("setsockopt"); 
        return ret; 
    }
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    if((ret = inet_pton(AF_INET, ipAddress, &address.sin_addr))<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return ret; 
    } 
    // Forcefully attaching socket to the port 8080 and address ip
    if ((ret = bind(_fd_session, (struct sockaddr *)&address, sizeof(address))) != 0) 
    {
        perror("bind"); 
        return ret; 
    }
    return 0;
}

int SockServer::Start()
{
    int ret;
    int addrlen = sizeof(address);
    if((ret = Create()) != 0)
    {
        printf("error when create socket\n");
        return ret;
    }
    if((ret = Setup()) != 0)
    {
        printf("error when setup socket\n");
        return ret;
    }
    printf("Listenning...\n");
    /**
     * wait for the client to approach the server to make connection
     * 10 : backlog to defines maximum length to which the queue of pending connections for _fd may grow
    */
    if ((ret = listen(_fd_session, 10)) < 0) 
    { 
        perror("listen");
        return ret; 
    }
    /**
     * accept the first connection request in queue
     * Create new connected socket and return new file descriptor for this socket
    */
    if ((_fd = accept(_fd_session, (struct sockaddr *)&address,  (socklen_t*)&addrlen)) < 0) 
    { 
        perror("error accept client"); 
        return ret;  
    }
    printf("Connected!\n");
    EchangeHostName(_fd);
    ret = EchangeMessage();
    return ret;
}

void SockServer::Close()
{
    if (!ipAddress)
    {
        free(ipAddress);
        ipAddress = NULL;
    }
    if (!name) {
        free(name);
        name = NULL;
    }
    if (!namepeer) {
        free(namepeer);
        namepeer = NULL;
    }
    printf("Disconnected\n");
    exit(EXIT_SUCCESS);
}