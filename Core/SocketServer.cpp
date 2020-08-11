/*
 * @Author: Kanade
 * @Date: 2020-08-09 23:03:28
 * @LastEditTime: 2020-08-11 19:28:44
 * @Description: 
 */
#include"SocketServer.h"
#include"../headers.h"
#include"../Miscellaneous/Log.h"

Log* logHelper;

SocketServer::SocketServer(int port, std::list<std::string> & messages, std::list<int> & connections) :_connections(connections), _messages(messages){
    try{
        _stop = false;
        _port = port;
        _server_fd = socket(AF_INET, SOCK_STREAM, 0);
        _client_addr_len = sizeof(_client_addr);
        long val;
        _timeout = {1, 500};

        if(_server_fd == -1){
            throw SocketError();
        }
        _addr.sin_family = AF_INET;
        _addr.sin_port = htons(_port);
        _addr.sin_addr.s_addr = htonl(INADDR_ANY);
        val = fcntl(_server_fd, F_GETFL);
        val |= O_NONBLOCK;
        fcntl(_server_fd, F_SETFL, val);
        if(bind(_server_fd, (struct sockaddr *) &_addr, sizeof(struct sockaddr_in)) == -1){
            throw BindingError();
        }

        if(listen(_server_fd, 511) == -1){
            throw ListeningError();
        }

        logHelper = new Log("Socket Server Initiated", general, "SocketServer", 1, 1);
        delete logHelper;
    }catch(std::exception& e){
        logHelper = new Log((string)e.what(), error, "SocketServer", 1, 1);
        delete logHelper;
    }
}

bool SocketServer::stop(){
    _stop = true;
    return true;
}

bool SocketServer::getStatus(){
    return _stop?false:true;
}

bool SocketServer::startLoop(){
    try{
        _stop = false;
        int new_connection{0}, current_connections{0};
        while(1){
            if(_stop){
                logHelper = new Log("Socket Server Stoped", warning, "SocketServer", 1, 1);
                delete logHelper;
                return 0;
            }
            new_connection = accept(_server_fd, (struct sockaddr*) &_client_addr, &_client_addr_len);
            if(new_connection != -1){
                std::cout<<new_connection<<std::endl;
                _connections.push_back(new_connection);
                logHelper = new Log("New Connection Accepted("+to_string(_connections.size())+") ", general, "SocketServer", 1, 1);
                delete logHelper;
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
                        if(mes == "!quit"){
                            logHelper = new Log("Connection Closed by Client", general, "SocketServer", 1, 1);
                            delete logHelper;
                            write(*current_socket, "Bye! (Connection Closed)", sizeof("Bye! (Connection Closed)"));
                            _connections.erase(current_socket);
                            break;
                        }else if(mes == "!m"){
                            write(*current_socket, "HISTORY MESSAGES====================\n", sizeof("HISTORY MESSAGES====================\n"));
                            for(string currentMessage : _messages){
                                currentMessage += '\n';
                                char result[currentMessage.length()+1];
                                strcpy(result, currentMessage.c_str());
                                write(*current_socket, result, sizeof(result));
                            }
                            write(*current_socket, "END MESSAGES========================\n", sizeof("END MESSAGES========================\n"));
                        }else{
                            if(mes!=""){
                                struct sockaddr_in* pV4Addr = (struct sockaddr_in*)&_client_addr;
                                struct in_addr IpAddr = pV4Addr->sin_addr;
                                char str[INET_ADDRSTRLEN];
                                inet_ntop(AF_INET, &IpAddr, str, INET_ADDRSTRLEN);
                                logHelper = new Log("New Message Saved", general, str, 1, 1);
                                _messages.push_back(mes);
                            }
                        }
                    }
                }
            }
        }
    }catch(std::exception& e){
        logHelper = new Log((string)e.what(), error, "SocketServer", 1, 1);
        delete logHelper;
        return false;
    }
}
