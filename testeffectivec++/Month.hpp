#ifndef _MONTH_HPP_
#define _MONTH_HPP_
#include <string>
class Month
{
public:
    explicit Month(int m = 1) : month(m) {}
    Month(const Month &m) : month(m.month) {}
    static Month Jan() { return Month(1); }
    static Month Feb() { return Month(2); }
    static Month Mar() { return Month(3); }
    static Month Apr() { return Month(4); }
    static Month May() { return Month(5); }
    static Month Jun() { return Month(6); }
    static Month Jul() { return Month(7); }
    static Month Aug() { return Month(8); }
    static Month Sept() { return Month(9); }
    static Month Oct() { return Month(10); }
    static Month Nov() { return Month(11); }
    static Month Dec() { return Month(12); }
    ~Month() = default;
    std::string getMonth() const { return monthnames[month - 1]; }

public:
    static const std::string monthnames[];

private:
    int month;
};

const std::string Month::monthnames[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sept", "Oct", "Nov", "Dec"};

#endif // !_MONTH_HPP_

/* int Month::getDays(bool isLeapYear) const
{
    if (month == 2)
    {
        if (isLeapYear)
            return 29;
        else
            return 28;
    }
    else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        return 31;
    else
        return 30;
} */