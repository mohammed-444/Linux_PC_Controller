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





Server::Server(short Port):port{Port},socketID{-1},new_socketID{-1}
{
    struct sockaddr_in address;
    memset(&address,0,sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);

    socketID = socket(AF_INET, SOCK_STREAM, 0); 
  
    if (socketID == -1) 
        { 
            std::cout<< "Create Socket Error!" << std::endl;
            exit(1); 
        }
        else
        {
            std::cout<< "Created Socket" << std::endl;
        } 

        // Forcefully attaching socket to the port 8080
    if (bind(socketID, (struct sockaddr*)&address,sizeof(address)) < 0) 
    {
        std::cout<< "binding Socket Error!" << std::endl;
        exit(1); 
    }
    else
    {
        std::cout<< "binded the Socket " << std::endl;
    } 
}

void Server::Start_Server()
{
    if (listen(socketID, 3) < 0) 
    {
        perror("listen error");
        exit(EXIT_FAILURE);
    }
}

void Server::Start_receiver()
{
    char buffer[100];
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
    if ((new_socketID= accept(socketID, NULL,NULL))< 0) 
    {
        perror("accept error");
        exit(EXIT_FAILURE);
    }    
    else
    {   
        std::cout << "accepted ..." <<std::endl;
    }

    send(new_socketID,helpMsg,strlen(helpMsg),0);
    
    while(1)
    {

    

    memset(buffer,0,sizeof(buffer));
    
    recv(new_socketID,buffer,sizeof(buffer),0);

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


void Server::action(char buffer[])
{
    int pid = fork();
  
    if(pid == -1)
    {
        // pid == -1 means error occurred
        perror("fork  error");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        close(socketID);
        close(new_socketID);

      
        //------------------------------------------------
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


Server::~Server()
{
    close(socketID);
    close(new_socketID);

}





