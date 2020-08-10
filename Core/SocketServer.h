/*
 * @Author: Kanade
 * @Date: 2020-08-09 23:03:20
 * @LastEditTime: 2020-08-10 11:57:24
 * @Description: 
 */
#include<list>
#include<string>
#include <algorithm>

#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H
class SocketServer{
    public:
        SocketServer(int, std::list<std::string>&, std::list<int>&);
        bool start();
        bool detach();
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
};
#endif