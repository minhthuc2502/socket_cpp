#ifndef SOCK_SERVER_HPP
#define SOCK_SERVER_HPP
#include "socket.hpp"
#include <netinet/in.h>
#include <sys/socket.h> 
#include <unistd.h>

class SockServer : public Socket
{
private:
    int _fd_session;
    int Setup();
public:
    SockServer() {};
    SockServer(int p, char* ad, char* cname) : Socket(p,ad,cname) {};
    ~SockServer() {};
    int Create();
    int Start();
    void Close();
};

#endif