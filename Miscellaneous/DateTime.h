/*
 * @Author: Kanade
 * @Date: 2020-08-07 19:45:55
 * @LastEditTime: 2020-08-10 15:09:00
 * @Description: 
 */
#include<string>
using namespace std;
#ifndef DATETIME_H
#define DATETIME_H
static const string month[12] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};
class DateTime{
    private:
    short _year;
    string _month;
    short _day;
    short _hour;
    short _minute;
    short _second;
    public:
    /** 
     * Summary: Create a new instance of DateTime use current time
     * Parameters:
     *  None
     * Return DateTime
    */
    DateTime();
    /** 
     * Summary: Create a new instance of DateTime use manually
     * Parameters:
     *  year -> short
     *  month -> short
     *  day -> short
     *  hour -> short
     *  minute -> short
     *  second -> short
    */
    DateTime(short, short, short, short, short, short);
    string toString();
    /** 
     * Summary: Return current time only
     * Parameters:
     *  ShowSecond -> bool
    */
    string getTime(bool);
    string getDate();
};
#endif