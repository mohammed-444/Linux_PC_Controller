#include "Server.hpp"

int main() 
{ 
    Server s(5000);

    s.Start_Server();

    s.Start_receiver();
    
    return 0;
}