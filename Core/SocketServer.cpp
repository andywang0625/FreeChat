/*
 * @Author: Kanade
 * @Date: 2020-08-09 23:03:28
 * @LastEditTime: 2020-08-10 15:30:10
 * @Description: 
 */
#include"SocketServer.h"
#include"../headers.h"


SocketServer::SocketServer(int port, std::list<std::string> & messages, std::list<int> & connections) :_connections(connections), _messages(messages){
    _stop = false;
    _port = port;
    _server_fd = socket(AF_INET, SOCK_STREAM, 0);
    _client_addr_len = sizeof(_client_addr);
    long val;
    _timeout = {1, 500};

    if(_server_fd == -1){
        std::cout<<"Socket Error"<<std::endl;
    }
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(_port);
    _addr.sin_addr.s_addr = htonl(INADDR_ANY);
    val = fcntl(_server_fd, F_GETFL);
    val |= O_NONBLOCK;
    fcntl(_server_fd, F_SETFL, val);
    if(bind(_server_fd, (struct sockaddr *) &_addr, sizeof(struct sockaddr_in)) == -1){
        std::cout<<"Binding Error"<<std::endl;
    }

    if(listen(_server_fd, 511) == -1){
        std::cout<<"Listen Error"<<std::endl;
    }

    std::cout<<"Socket Server Inited."<<std::endl;
}

bool SocketServer::stop(){
    _stop = true;
    return true;
}

bool SocketServer::getStatus(){
    return _stop?false:true;
}

bool SocketServer::startLoop(){
    _stop = false;
    int new_connection{0}, current_connections{0};
    while(1){
        if(_stop){
            std::cout<<"Socket Server Stoped."<<std::endl;
            return 0;
        }
        new_connection = accept(_server_fd, (struct sockaddr*) &_client_addr, &_client_addr_len);
        if(new_connection != -1){
            std::cout<<new_connection<<std::endl;
            _connections.push_back(new_connection);
            std::cout<<"New Connect Accepted ("<<_connections.size()<<")"<<std::endl;
        }

        FD_ZERO(&_fdset);
        for(auto current_socket : _connections){
            FD_SET(current_socket, &_fdset);
        }

        select(_connections.back()+1, &_fdset, NULL, NULL, &_timeout);

        char buf[255];
        for(auto current_socket = _connections.begin(); current_socket != _connections.end(); current_socket++){
            if(FD_ISSET(*current_socket, &_fdset)){
                memset(buf, 0, sizeof(buf));
                std::string mes;
                if(recv(*current_socket, buf, sizeof(buf), 0)){
                    mes = (std::string)buf;
                    _stripUnicode(mes);
                    std::cout<<mes<<" - Length:"<<mes.length()<<std::endl;
                    if(mes == "!quit"){
                        std::cout<<"Connection Closed"<<std::endl;
                        write(*current_socket, "Bye! (Connection Closed)", sizeof("Bye! (Connection Closed)"));
                        _connections.erase(current_socket);
                        break;
                    }
                }
            }
        }
    }
}
