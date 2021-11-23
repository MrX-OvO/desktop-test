#ifndef _DAY_HPP_
#define _DAY_HPP_
#include <string>
class Day
{
public:
    explicit Day(int d = 1) : day(d) {}
    Day(const Day &d) : day(d.day) {}
    ~Day() = default;
    std::string getDay() const { return std::to_string(day); }

private:
    int day;
};
#endif // !_DAY_HPP_