/*
 * @Author: Kanade
 * @Date: 2020-08-10 17:23:55
 * @LastEditTime: 2020-08-12 17:17:42
 * @Description: 
 */
#include<string>
#include"../Miscellaneous/DateTime.h"
#include"../Miscellaneous/Log.h"

#ifndef MESSAGE_H
#define MESSAGE_H

class Message{
    public:
        Message(string, string, DateTime);
        //~Message();
        string toString();
    private:
        string _messageBody;
        string _messageSender;
        DateTime _time;
};


#endif