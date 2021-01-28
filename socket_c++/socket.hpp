#ifndef SOCKET_CPP_H
#define SOCKET_CPP_H

#include <stdio.h>
#include <thread>
#include <string.h>
#include <netinet/in.h>
#include <mutex>
#include <condition_variable>
using namespace std;

class Socket
{
private:
    bool wait_thread = false;
    mutex wait_mutex;
    condition_variable cv_end;
    thread read_socket;     // thread to read message from the peer
    thread write_socket;    // thread to write message to the peer
    void read_event();      // function callback attach thread read_socket
    void write_event();     // function callback attach thread write_socket
protected:
    char* ipAddress;
    char* name;             // name of socket
    char* namepeer;         // name of peer in the communication
    int port;               // port
    int _fd;
    struct sockaddr_in address; 
public:
    /**
     * Constructor
    */
    Socket() : ipAddress(NULL), name(NULL), namepeer(NULL), port(0), _fd(0) {};
    /**
     * Constructor
    */
    Socket(int p, char* ad, char* cname);
    /**
     * Desstructor
    */
    ~Socket() {};
    /**
     * Methode to create socket
    */
    int Create();
    /**
     * Methode to exchange messages
     * Start thread read and write
    */
    int EchangeMessage();
    /**
     * Methode to setup a socket and connect to the peer
    */
    int Start();
    /**
     * Free memory and disconnect with peer
    */
    void Close();
    /**
     * Method to keep thread run
    */
    void Wait();
    /**
     * Notify a stop request to finish the threads
    */
    void StopWait();
    /**
     * Exchange name of socket each other
    */
    int EchangeHostName(int fd);
    /**
     * Getter to get wait_thread
    */
    bool getwait_thread();
};

#endif