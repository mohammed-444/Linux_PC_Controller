#ifndef SERVER_H
#define SERVER_H

class Server
{
private:
    // var to contain the port number the socket will connect to
    short port;
    // file descriptor for the passive socket
    int socketID;
    // file descriptor for the active socket 
    int new_socketID;

public:
    // delete the constructor to prevent from using without specifing the port number
    Server() = delete;
    // constructor that take the port number to initailize the socket and bind it to the port
    Server(short port);
    // function that enable the passive socket to start listening 
    void Start_Server();
    // function that accept the connection request and start receiving the messages contain the super loop
    void Start_receiver();
    // take the received message then do the specified action change it to your liking
    void action(char buffer[]);
    // close the active and passive socket
    ~Server();

    
};

#endif