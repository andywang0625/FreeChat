/*
 * @Author: Kanade
 * @Date: 2020-08-07 19:38:17
 * @LastEditTime: 2020-08-11 17:48:46
 * @Description: 
 */
#include<string>
#include"DateTime.h"
using namespace std;
#ifndef LOG_H
#define LOG_H
enum LogType{
    general,
    error,
    warning,
};
class Log{
    public:
    Log(string, LogType, string, bool, bool);
    static void print(string, LogType, string);
    static void save(string, LogType, string);
    bool save();
    private:
    string _message;
    LogType _type;
    string _source;
    DateTime *_time;
};
#endif