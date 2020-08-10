/*
 * @Author: Kanade
 * @Date: 2020-08-07 19:46:17
 * @LastEditTime: 2020-08-10 15:11:06
 * @Description: 
 */
#include "DateTime.h"
#include <ctime>
#include <iostream>

using namespace std;
DateTime::DateTime(){
    time_t now = time(0);
    tm *gmtm = gmtime(&now);
    _year = (short) gmtm->tm_year+1900;
    _month = month[gmtm->tm_mon];
    _day = gmtm->tm_mday;
    _hour = gmtm->tm_hour;
    _minute = gmtm->tm_min;
    _second = gmtm->tm_sec;
}

string DateTime::toString(){
    return to_string(this->_year)+" "+
    this->_month+" "+
    to_string(this->_hour)+" "+
    to_string(this->_minute)+" "+
    to_string(this->_second);
}
