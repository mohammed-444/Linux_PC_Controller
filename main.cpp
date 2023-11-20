#include "Server.hpp"

int main() 
{ 
    // constructor that take the port number to initailize the socket and bind it to the port
    Server s(5000);
    // function that enable the passive socket to start listening for requists
    s.Start_Server();
    // function that accept the connection request and start receiving the messages contain the super loop
    s.Start_receiver();
    
    return 0;
}