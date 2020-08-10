/*
 * @Author: Kanade
 * @Date: 2020-08-07 18:44:53
 * @LastEditTime: 2020-08-10 11:57:34
 * @Description: 
 */
#include"headers.h"
#include"Core/SocketServer.h"

int main(int argc, char * argv[]){

    std::cout<<"FreeChat Server is Initiating"<<std::endl;

    std::list<std::string> messages;
    std::list<int> connections;

    SocketServer server(atoi(argv[1]), messages, connections);
    server.start();
}
