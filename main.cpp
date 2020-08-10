/*
 * @Author: Kanade
 * @Date: 2020-08-07 18:44:53
 * @LastEditTime: 2020-08-09 22:52:32
 * @Description: 
 */
#include"headers.h"

bool invalidChar (char c){
    if(c=='\n'||c=='\0')
        return true;
    else
        return false;
}

void stripUnicode(std::string &str)
{
    str.erase(remove_if(str.begin(),str.end(), invalidChar), str.end());
}

int main(int argc, char * argv[]){

    std::cout<<"FreeChat Server is Initiating"<<std::endl;

    std::list<std::string> messages;
    std::list<int> connections;
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
    addr.sin_port = htons(atoi(argv[1]));
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    val = fcntl(server_fd, F_GETFL);
    val |= O_NONBLOCK;
    fcntl(server_fd, F_SETFL, val);

    // struct sigaction myaction;
    // myaction.sa_handler = SIG_IGN;
    // sigaction(SIGPIPE, &myaction, NULL);

    if(bind(server_fd, (struct sockaddr *) &addr, sizeof(struct sockaddr_in)) == -1){
        std::cout<<"Binding Error"<<std::endl;
    }

    if(listen(server_fd, 511) == -1){
        std::cout<<"Listen Error"<<std::endl;
    }

    int new_connection, current_connections{0};

    while(1){
        new_connection = accept(server_fd, (struct sockaddr*) &client_addr, &client_addr_len);
        if(new_connection != -1){
            std::cout<<new_connection<<std::endl;
            connections.push_back(new_connection);
            std::cout<<"New Connect Accepted ("<<connections.size()<<")"<<std::endl;
        }

        FD_ZERO(&fdset);
        for(auto current_socket : connections){
            FD_SET(current_socket, &fdset);
        }

        select(connections.back()+1, &fdset, NULL, NULL, &timeout);

        char buf[255];
        for(auto current_socket = connections.begin(); current_socket != connections.end(); current_socket++){
            if(FD_ISSET(*current_socket, &fdset)){
                memset(buf, 0, sizeof(buf));
                std::string mes;
                if(recv(*current_socket, buf, sizeof(buf), 0)){
                    mes = (std::string)buf;
                    stripUnicode(mes);
                    std::cout<<mes<<" - Length:"<<mes.length()<<std::endl;
                    if(mes == "!quit"){
                        std::cout<<"Connection Closed"<<std::endl;
                        write(*current_socket, "Bye! (Connection Closed)", sizeof("Connection Closed"));
                        connections.erase(current_socket);
                        break;
                    }
                }
            }
        }
    }
}
