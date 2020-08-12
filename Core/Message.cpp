/*
 * @Author: Kanade
 * @Date: 2020-08-10 17:24:01
 * @LastEditTime: 2020-08-12 17:16:19
 * @Description: 
 */
#include"Message.h"
#include"../Miscellaneous/Log.h"
#include<string>
using namespace std;

Log* logHelper;

Message::Message(string message, string sender, DateTime time){
    _messageBody = message;
    _messageSender = message;
    _time = time;
}

string Message::toString(){
    string str = _time.toString()+": ("+_messageSender+") "+_messageBody;
}