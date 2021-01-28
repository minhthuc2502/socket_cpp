#include "../include/sockclient.hpp"

int SockClient::Create()
{
    /**
     * Create socket with 
     * Domain: integer, communication domain e.g., AF_INET (IPv4 protocol) , AF_INET6 (IPv6 protocol)
     * type: communication type
     *  SOCK_STREAM: TCP(reliable, connection oriented)
     *  SOCK_DGRAM: UDP(unreliable, connectionless)
     * 0 : Protocol value for Internet Protocol(IP)
    */
    if ((_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        perror("socket failed"); 
        return -1; 
    }
    return 0;   
}

int SockClient::Start()
{
    int ret;
    if((ret = Create()) != 0)
    {
        printf("error when create socket\n");
        return ret;
    }
    address.sin_family = AF_INET; 
    address.sin_port = htons(port); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if((ret = inet_pton(AF_INET, ipAddress, &address.sin_addr))<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return ret; 
    } 
    printf("Connecting to server...\n");
    /**
     * connect request from client
     * connect to socket referred to by file descriptor _fd to the address specified by address
    */
    while ((ret = connect(_fd, (struct sockaddr *)&address, sizeof(address))) < 0);
    printf("Connected\n");
    EchangeHostName(_fd);
    ret = EchangeMessage();
    return ret;
}

void SockClient::Close()
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