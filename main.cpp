/*
 * @Author: Kanade
 * @Date: 2020-08-07 18:44:53
 * @LastEditTime: 2020-08-11 18:23:39
 * @Description: 
 */
#include"headers.h"
#include"Core/SocketServer.h"
#include"Miscellaneous/DateTime.h"
#include"Miscellaneous/Log.h"

std::mutex g_mutex;

int main(int argc, char * argv[]){
    Log *log;

    log = new Log("FreeChat Server is Initiating", general, "Kernel", 1, 1);
    delete log;

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
        }else if(command == "/testlog"){
            log = new Log("test log", general, "Console", 1, 1);
            delete log;
            log = new Log("test warning", warning, "Console", 1, 1);
            delete log;
            log = new Log("test error", error, "Console", 1, 1);
            delete log;
        }else{
            log = new Log("Command Not Found", error, "Console", 1, 0);
        }
    }
}
