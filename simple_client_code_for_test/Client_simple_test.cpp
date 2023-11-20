#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>


int main() 
{ 
  int socketID;
  // std::string input;
  char buffer[1024]="hi I'm mohammed";
  struct sockaddr_in address;
  memset(&address,0,sizeof(address));
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr("127.0.0.1");
  address.sin_port = htons(5000);


  socketID = socket(AF_INET, SOCK_STREAM, 0); 
  
  if(socketID == -1) 
  { 
    std::cout<< "Create Socket Error!" << std::endl;
    exit(1); 
  } 

  int error = connect(socketID ,reinterpret_cast<sockaddr *> (&address) ,sizeof(address));
  if(error != 0)
  {
    std::cout<< "connection error Error!" << std::endl;
    exit(1); 
  }
 while(1)
 {
  std::cin >> buffer ;
  
  send(socketID,buffer,sizeof(buffer),0);

  memset(buffer,0,1024);
  
  recv(socketID,buffer,sizeof(buffer),0);

  std::cout << buffer <<std::endl;

 }
  std::cout << socketID <<std::endl;
  std::cout << sizeof(address) <<std::endl;
  close(socketID);

  return 0;
}