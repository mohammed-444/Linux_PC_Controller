#ifndef SERVER_H
#define SERVER_H

class Server
{
private:

    short port;
    int socketID;
    int new_socketID;

public:

    Server() = delete;

    Server(short port);

    void Start_Server();

    void Start_receiver();

    void action(char buffer[]);
    
    ~Server();

    
};

#endif