/*
 * @Author: Kanade
 * @Date: 2020-08-07 19:45:55
 * @LastEditTime: 2020-08-07 19:58:28
 * @Description: 
 */
#include<string>
using namespace std;
#ifndef DATETIME_H
#define DATETIME_H
enum month{
    January,
    February,
    March,
    April,
    May,
    June,
    July,
    Auguest,
    September,
    October,
    November,
    December
};
class DateTime{
    private:
    short _year;
    month _month;
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
     *  month -> enum month
     *  day -> short
     *  hour -> short
     *  minute -> short
     *  second -> short
    */
    DateTime(short, month, short, short, short, short);
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