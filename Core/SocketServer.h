/*
 * @Author: Kanade
 * @Date: 2020-08-09 23:03:20
 * @LastEditTime: 2020-08-10 15:27:51
 * @Description: 
 */
#include"../headers.h"

#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H
class SocketServer{
    public:
        SocketServer(int, std::list<std::string>&, std::list<int>&);
        bool startLoop();
        bool getStatus();
        bool stop();
        static void _stripUnicode(std::string& str){
            str.erase(std::remove_if(str.begin(),str.end(), _invalidChar), str.end());
        };
        static bool _invalidChar (char c){
            if(c=='\n'||c=='\0')
                return true;
            else
                return false;
        };
    private:
        bool _stop;
        std::list<std::string>& _messages;
        std::list<int>& _connections;
        int _port;
        int _server_fd;
        struct sockaddr_in _client_addr;
        struct sockaddr_in _addr;
        fd_set _fdset;
        socklen_t _client_addr_len;
        struct timeval _timeout;
};
#endif