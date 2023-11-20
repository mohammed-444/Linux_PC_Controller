#include "Server.hpp"

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include "string.h"


// constructor that take the port number to initailize the socket and bind it to the port

Server::Server(short Port):port{Port},socketID{-1},new_socketID{-1}
{   // build in struct needed to initialize and bind the socket
    struct sockaddr_in address;
    // clearing the space with zeros
    memset(&address,0,sizeof(address));
    // config the family, ip and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);
    // config the family, domain and protocol
    socketID = socket(AF_INET, SOCK_STREAM, 0); 
   // checking for error if the return is -1
    if (socketID == -1) 
    { 
        std::cout<< "Create Socket Error!" << std::endl;
        exit(EXIT_FAILURE); 
    }
    else
    {
        std::cout<< "Created Socket" << std::endl;
    } 

        // attaching socket to the port and checking for error
    if (bind(socketID, (struct sockaddr*)&address,sizeof(address)) < 0) 
    {
        std::cout<< "binding Socket Error!" << std::endl;
        exit(EXIT_FAILURE); 
    }
    else
    {
        std::cout<< "binded the Socket " << std::endl;
    } 
}
 // function that enable the passive socket to start listening 
void Server::Start_Server()
{
    //checking for error
    if (listen(socketID, 3) < 0) 
    {
        perror("listen error");
        exit(EXIT_FAILURE);
    }
}
 // function that accept the connection request and start receiving the messages contain the super loop
void Server::Start_receiver()
{
    // buffer to hold the received message 
    char buffer[100];
    // hold the send message for the client
    char * helpMsg = (char *)"--------------------------------\n"
                    "help menu \n"
                    "--------------------------------\n "
                    "Type any commands Number:\n"
                    "1. terminal\n"
                    "2. calendar\n" 
                    "3. firefox\n"
                    "4. nautilus\n"
                    "5. sudoku\n"
                    "6. calculator\n"
                    "Type q to quit\n"
                    
                    "--------------------------------\n";
    // accept the client and create an active socket to start the communication                
    if ((new_socketID= accept(socketID, NULL,NULL))< 0) 
    {
        perror("accept error");
        exit(EXIT_FAILURE);
    }    
    else
    {   
        std::cout << "accepted ..." <<std::endl;
    }

    // send the start message
    send(new_socketID,helpMsg,strlen(helpMsg),0);
    
    while(1)
    {
        // clear the received buffer
        memset(buffer,0,sizeof(buffer));
        // block the code hear until received
        recv(new_socketID,buffer,sizeof(buffer),0);

        // check if the client want to quit or the input wrong
        if(buffer[0] =='q')
        {   
            const char* errorMessage = "server closing ....";
            send(new_socketID, errorMessage, strlen(errorMessage), 0);
            std::cout << "server closing ...." << std::endl;
            break;
        }
        else if (buffer[0] >'6' || buffer[0] <'1')
        {
            const char* errorMessage = "Wrong Command Number!!";
            send(new_socketID, errorMessage, strlen(errorMessage), 0);
            std::cout << "Wrong command Number" << std::endl;
        } 
        else
        {
            action(buffer);
        }
    
    }

}

// take the received message then do the specified action change it to your liking
void Server::action(char buffer[])
{
    // fork the process to create sperated process for the task 
    int pid = fork();
    // checking for error
    if(pid == -1)
    {
        // pid == -1 means error occurred
        perror("fork  error");
        exit(EXIT_FAILURE);
    }
    // enter only if it is the new child process
    else if (pid == 0)
    {
        // close the socket for the new process not needed anymore
        close(socketID);
        close(new_socketID);

      
        //------------------------------------------------
        //switch process to the wanted action process using execlp
        if (buffer[0]=='1') 
        {
            execlp("gnome-terminal", "gnome-terminal", NULL);
            perror("execv gnome-termina error");
            exit(EXIT_FAILURE);
        } 
        else if (buffer[0]=='2')
        {
            
            execlp("gnome-calendar", "gnome-calendar", NULL);
            perror("execv gnome-termina error");
            exit(EXIT_FAILURE);
        } 
        else if (buffer[0]=='3') 
        {
            execlp("firefox", "firefox", NULL);
            perror("execv error");
            exit(EXIT_FAILURE);
        } 
        else if (buffer[0]=='4') 
        {
            
            execlp("nautilus", "nautilus", NULL);
            perror("execv nautilus error");
            exit(EXIT_FAILURE);
        } 
        else if (buffer[0]=='5') 
        {
            
            execlp("gnome-sudoku", "ggnome-sudoku", NULL);
            perror("execv gnome-sudokuerror");
            exit(EXIT_FAILURE);
        } 
        else if (buffer[0]=='6') 
        {
            execlp("gnome-calculator", "gnome-calculator", NULL);
            perror("execv gnome-calculatorerror");
            exit(EXIT_FAILURE);
        } 

        
        
    }
    else
    {

    }
}

// close the active and passive socket
Server::~Server()
{
    close(socketID);
    close(new_socketID);

}





