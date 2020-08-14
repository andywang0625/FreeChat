/*
 * @Author: Kanade
 * @Date: 2020-08-10 17:24:01
 * @LastEditTime: 2020-08-12 17:32:04
 * @Description: 
 */
#include"Message.h"
#include<string>
using namespace std;

Message::Message(string message, string sender, DateTime time){
    _messageBody = message;
    _messageSender = sender;
    _time = time;
}

string Message::toString(){
    string str = _time.toString()+": ("+_messageSender+") "+_messageBody;
    return str;
}

// Message::~Message(){
//     Log* logHelper;
//     logHelper = new Log("A Message Has Been Destoryed", general, "Message", 1, 0);
//     delete logHelper;
// }