#ifndef _DATA_HPP_
#define _DATA_HPP_
#include <string>
#include "Day.hpp"
#include "Month.hpp"
#include "Year.hpp"
class Date
{
public:
    explicit Date(int, int, int);
    explicit Date(const Day &d, const Month &m, const Year &y) : day(d), month(m), year(y) {}
    Date(const Date &date) : year(date.year), month(date.month), day(date.day) {}
    ~Date() = default;
    const std::string getDate() const { return month.getMonth() + " " + day.getDay() + " " + year.getYear(); }

private:
    Year year;
    Month month;
    Day day;
};

Date::Date(int d = 1, int m = 1, int y = 1960) : year(Year(y))
{
    d = (d >= 1 && d <= 31 ? d : 1);
    if (m <= 1 || m > 12)
        month = Month::Jan();
    else
    {
        switch (m)
        {
        case 2:
            month = Month::Feb();
            if (year.isLeapYear())
                d = (d >= 1 && d <= 29 ? d : 1);
            else
                d = (d >= 1 && d <= 28 ? d : 1);
            break;
        case 3:
            month = Month::Mar();
            break;
        case 5:
            month = Month::May();
            break;
        case 7:
            month = Month::Jul();
            break;
        case 8:
            month = Month::Aug();
            break;
        case 10:
            month = Month::Oct();
            break;
        case 12:
            month = Month::Dec();
            break;
        case 4:
            month = Month::Apr();
            break;
        case 6:
            month = Month::Jun();
            break;
        case 9:
            month = Month::Sept();
            break;
        case 11:
            month = Month::Nov();
            break;
        }
    }
    if (m == 4 || m == 6 || m == 9 || m == 11)
        d = (d >= 1 && d <= 30 ? d : 1);
    day = Day(d);
}

#endif // !_DATA_HPP_
