#include "socket.hpp"
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <termios.h>

using namespace std;
// Get first character in message
static char getch(void)
{
    char buf = 0;
    struct termios old;
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}

// return first character
static char check_press_key()
{
    char chk;
    chk=getch();
    return chk;
}

Socket::Socket(int p, char* ad, char* cname)
{
    port = p;
    ipAddress = new (char)(strlen(ad)/8 + 1);
    memset(ipAddress,0,strlen(ad));
    strcpy(ipAddress,ad);
    name = new (char)(strlen(cname)/8 + 1);
    memset(name,0,strlen(cname));
    strcpy(name,cname);
}

void Socket::read_event()
{
    char buffer[1024] = {0};
    int ret = 0;
    while(1)
    {
        ret = read(_fd , buffer, 1024);
        if(ret < 0)
        {
            perror("ERROR reading from socket");
            break;
        }
        else if (ret == 0)
        {
            StopWait();
            printf("Disconnect from interlocutor\n");
            break;
        }
        if(buffer[0] != '\0')
            cout<<namepeer<<": "<<buffer<<endl;
        memset(buffer,0,1024);   
    }
}

void Socket::write_event()
{
    char message[1024] = {0};
    char *strchar = new char[1024];
    int ret = 0;
    while(1)
    {
        strchar[0] = check_press_key();
        cout<<name<<": "<<strchar[0];
        scanf("%[^\n]%*c",message);
        strcat(strchar,message);
        ret = send(_fd , strchar, strlen(strchar) , 0);
        if(ret < 0)
        {
            perror("ERROR writing to socket");
            break;
        }
        memset(strchar,0,strlen(strchar));
    }
    free(strchar);
}

int Socket::EchangeMessage()
{
    printf("Start communication\n");
    wait_thread = true;
    read_socket = std::thread(&Socket::read_event, this);
    write_socket = std::thread(&Socket::write_event, this);
    return 0;
}

void Socket::Wait()
{
    std::unique_lock<std::mutex> lock(wait_mutex);
    cv_end.wait(lock);
    printf("Finish waiting\n");
}

void Socket::StopWait()
{
    {
        wait_thread = false;
        cv_end.notify_all();
    }
}

int Socket::EchangeHostName(int fd)
{
    namepeer = new char[1024];
    send(fd, name, strlen(name),0);
    read(fd, namepeer, 1024);
    return 0;
}

bool Socket::getwait_thread()
{
    return wait_thread;
}
