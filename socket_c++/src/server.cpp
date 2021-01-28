#include <stdio.h>
#include "../include/sockserver.hpp"
#include <iostream>
#include <signal.h>
#include <getopt.h>
using namespace std;

SockServer* pServer;

/**
 *print usage of option
 */
void usage(){
  printf("--port port | port listening\n");
  printf("--address ipaddress");
  printf("--name name | name of socket");
  printf("--help help affiche all options\n");
}

static void signal_close(int signal)
{
    printf("signal %d handler\n",signal);
    if (pServer->getwait_thread())
        pServer->StopWait();
    else {
        pServer->Close();
    }
    return;
}

int main(int argc, char* argv[])
{
    int port = 0;
    char* name = NULL;
    char* ip = NULL;
    int o;
    int option_index;
    int index;
    static struct option long_options[] =
    {
        {"address", required_argument,  0 , 'a'},
        {"help", no_argument,  0 , 'h'},
        {"name", required_argument, 0, 'n'},
        {"port", required_argument, 0, 'p'},
        {0, 0, 0, 0},
    };
    while((o = getopt_long(argc,argv,"n:h:p:a:",long_options, &option_index)) != -1){
        switch (o)
        {
            case 'n':
            name = optarg;
            break;
            case 'p':
            port = atoi(optarg);
            break;
            case 'a':
            ip = optarg;
            break;  
            case 'h':
            usage();
            return EXIT_SUCCESS;
            case '?':
            if (optopt == 'n' || optopt == 'p' || optopt == 'a')
            {
                printf("Option -%c requires an argument. \n", optopt);
            }
            else if (isprint (optopt))
            {
                printf("Unknown option -%c.\n",optopt);
            }
            else
            {
                printf("Unknown option character \\x%x.\n", optopt);  
            }
            return 0;
            default:
            abort();
        }
    }
    for(index = optind; index < argc; index++)
    {
        printf("Non-option argument %s \n", argv[index]);
        return 0;
    }
    if (name == NULL || ip == NULL){
        printf("Invalid argument. See --help for more options\n");
    }
    else
    {
        int error = 0;
        signal(SIGINT, signal_close);
        SockServer server(port, ip, name);
        pServer = &server;
        error = server.Start();
        if(error != 0)
        {
            cerr<<"Error code: "<<error<<endl;
            return error;
        }
        server.Wait();
        server.Close();
    }
    return 0;
}