/*
 * @Author: Kanade
 * @Date: 2020-08-07 19:46:17
 * @LastEditTime: 2020-08-07 20:36:19
 * @Description: 
 */
#include "DateTime.h"
#include <ctime>

using namespace std;
DateTime::DateTime(){
    time_t now = time(0);
    tm *gmtm = gmtime(&now);
    _year = (short) gmtm->tm_year;
    /*
    switch (expression)
    {
    case :
        break;
    
    default:
        break;
    }
    */
}

