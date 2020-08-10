/*
 * @Author: Kanade
 * @Date: 2020-08-07 18:44:53
 * @LastEditTime: 2020-08-10 15:26:11
 * @Description: 
 */
#include"headers.h"
#include"Core/SocketServer.h"
#include"Miscellaneous/DateTime.h"

std::mutex g_mutex;

int main(int argc, char * argv[]){

    std::cout<<"FreeChat Server is Initiating"<<std::endl;

    std::list<std::string> messages;
    std::list<int> connections;

    SocketServer server(atoi(argv[1]), messages, connections);
    std::thread socketServerThread(&SocketServer::startLoop, &server);
    socketServerThread.detach();

    usleep(500);

    string command = "";
    while(1){
        std::cout<<"FreeChat$ ";
        cin>>command;
        if(command == "/time"){
            DateTime testTime;
            std::cout<<testTime.toString()<<std::endl;
        }else if(command == "/stop"){
            server.stop();
        }else if(command == "/start"){
            if(server.getStatus())
                std::cout<<"The server is running..."<<std::endl;
            else{
                std::thread socketServerThread(&SocketServer::startLoop, &server);
                socketServerThread.detach();
                usleep(500);
                std::cout<<"The server restarted..."<<std::endl;
            }
        }else{
            std::cout<<"Command Not Found"<<std::endl;
        }
    }
}
