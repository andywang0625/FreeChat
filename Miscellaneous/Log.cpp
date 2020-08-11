/*
 * @Author: Kanade
 * @Date: 2020-08-07 23:53:04
 * @LastEditTime: 2020-08-10 17:37:33
 * @Description: 
 */
#include"Log.h"
#include<iostream>
#include"DateTime.h"

Log::Log(string message, LogType type, string source){
    _message = message;
    _type = type;
    _source = source;
    _time = new DateTime();
}