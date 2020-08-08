/*
 * @Author: Kanade
 * @Date: 2020-08-07 19:38:17
 * @LastEditTime: 2020-08-07 19:44:35
 * @Description: 
 */
#include<string>
using namespace std;
#ifndef LOG_H
#define LOG_H
enum LogType{
    general,
    error,
    warning,
};
class Log{
    private:
    string _message;
    LogType _type;
    string _source;
    
};
#endif