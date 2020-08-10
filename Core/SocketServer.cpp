/*
 * @Author: Kanade
 * @Date: 2020-08-09 23:03:28
 * @LastEditTime: 2020-08-10 11:56:55
 * @Description: 
 */
#include"SocketServer.h"
#include"../headers.h"


SocketServer::SocketServer(int port, std::list<std::string> & messages, std::list<int> & connections) :_connections(connections), _messages(messages){
    _stop = false;
    _port = port;
}

bool SocketServer::start(){
    int new_connection{0}, current_connections{0};
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    fd_set fdset;
    long val;
    struct timeval timeout = {1, 500};

    if(server_fd == -1){
        std::cout<<"Socket Error"<<std::endl;
        return -1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(_port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    val = fcntl(server_fd, F_GETFL);
    val |= O_NONBLOCK;
    fcntl(server_fd, F_SETFL, val);

    if(bind(server_fd, (struct sockaddr *) &addr, sizeof(struct sockaddr_in)) == -1){
        std::cout<<"Binding Error"<<std::endl;
    }

    if(listen(server_fd, 511) == -1){
        std::cout<<"Listen Error"<<std::endl;
    }

    while(1){
        if(_stop)
            return 0;
        new_connection = accept(server_fd, (struct sockaddr*) &client_addr, &client_addr_len);
        if(new_connection != -1){
            std::cout<<new_connection<<std::endl;
            _connections.push_back(new_connection);
            std::cout<<"New Connect Accepted ("<<_connections.size()<<")"<<std::endl;
        }

        FD_ZERO(&fdset);
        for(auto current_socket : _connections){
            FD_SET(current_socket, &fdset);
        }

        select(_connections.back()+1, &fdset, NULL, NULL, &timeout);

        char buf[255];
        for(auto current_socket = _connections.begin(); current_socket != _connections.end(); current_socket++){
            if(FD_ISSET(*current_socket, &fdset)){
                memset(buf, 0, sizeof(buf));
                std::string mes;
                if(recv(*current_socket, buf, sizeof(buf), 0)){
                    mes = (std::string)buf;
                    _stripUnicode(mes);
                    std::cout<<mes<<" - Length:"<<mes.length()<<std::endl;
                    if(mes == "!quit"){
                        std::cout<<"Connection Closed"<<std::endl;
                        write(*current_socket, "Bye! (Connection Closed)", sizeof("Connection Closed"));
                        _connections.erase(current_socket);
                        break;
                    }
                }
            }
        }
    }
}
