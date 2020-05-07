# Overview
The project aims to create a socket which allow a server and a client can connect and communicate together

## Run application
- Download code source.
- Compile code source by typing on terminal :
```
$ make all
```

- Run application for example :
> server side:
 ```
$ ./server -p 8080 -a 127.0.0.1 -n server
```

> client side:
 ```
$ ./client -p 8080 -a 127.0.0.1 -n client
```

- Know more information about argument :
 ```
$ ./client --help
```
or
 ```
$ ./server --help
```
### Note

- The example is tested with ip address of `localhost`. If you want to communicate between the other machines, try to change ip address.
- To access the server, client needs to connect to the same network as server.