#ifndef SOCK_CLIENT_HPP
#define SOCK_CLIENT_HPP
#include "socket.hpp"
#include <netinet/in.h>
#include <sys/socket.h> 
#include <unistd.h>
#include <arpa/inet.h> 
class SockClient : public Socket
{
public:
    SockClient();
    SockClient(int p, char* ad, char* cname) : Socket(p,ad,cname) {};
    ~SockClient() {};
    int Create();
    int Start();
    void Close();
};
#endif