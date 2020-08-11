/*
 * @Author: Kanade
 * @Date: 2020-08-07 23:53:04
 * @LastEditTime: 2020-08-11 18:20:28
 * @Description: 
 */
#include"Log.h"
#include<fstream>
#include<iostream>
#include"DateTime.h"
using namespace std;

Log::Log(string message, LogType type, string source, bool print, bool save){
    _message = message;
    _type = type;
    _source = source;
    _time = new DateTime();
    try{
        if(print){
            if(type == general){
                cout<<"["<<_time->toString()<<"]("<<_source<<") - \033[32m"+_message+"\033[0m"<<endl;
                if(save){
                    ofstream outlog("FreeChat.log", ios::app);
                    outlog<<"GENERAL\t-\t["<<_time->toString()<<"]\t("<<_source<<")\t-\t"+_message<<endl;
                    outlog.close();
                }
            }else if(type == warning){
                cout<<"["<<_time->toString()<<"]("<<_source<<") - \033[33m"+_message+"\033[0m"<<endl;
                if(save){
                    ofstream outlog("FreeChat.log", ios::app);
                    outlog<<"WARNING\t-\t["<<_time->toString()<<"]\t("<<_source<<")\t-\t"+_message<<endl;
                    outlog.close();
                }
            }else if(type == error){
                cout<<"["<<_time->toString()<<"]("<<_source<<") - \033[31m"+_message+"\033[0m"<<endl;
                if(save){
                    ofstream outlog("FreeChat.log", ios::app);
                    outlog<<"ERROR\t-\t["<<_time->toString()<<"]\t("<<_source<<")\t-\t"+_message<<endl;
                    outlog.close();
                }
            }
        }
    }
    catch(int e){
        cout<<"An exception occurred in Log. Exception Nr. "<<e<<endl;
    }
}