/*
 * @Author: Kanade
 * @Date: 2020-08-07 19:32:25
 * @LastEditTime: 2020-08-07 19:40:08
 * @Description: 
 */
#include<string>
using namespace std;
#ifndef MESSAGE_H
#define MESSAGE_H
class Message{
    private:
    string _body;
    string _date;
    string _time;
    //string _sender;
    //string _reciver;
    public:
    Message(string body);
};
#endif