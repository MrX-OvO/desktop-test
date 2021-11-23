#ifndef _YEAR_HPP_
#define _YEAR_HPP_
#include <string>
class Year
{
public:
    explicit Year(int y = 1960) { year = (y >= 1960) ? y : 1960; }
    Year(const Year &y) : year(y.year) {}
    ~Year() = default;
    bool isLeapYear() const { return ((year & 3) == 0) && (year % 100 != 0 || year % 400 == 0); }
    std::string getYear() const { return std::to_string(year); }

private:
    int year;
};
#endif // !_YEAR_HPP_
