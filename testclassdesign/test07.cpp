#include <iostream>
class Date;
class Time
{
    friend class Date;

private:
    size_t hour;
    size_t minute;
    size_t second;
    size_t carry_or_borrow;

private:
    void operatorPlus(size_t &, size_t &, size_t &, size_t &);
    void operatorMinus(size_t &, size_t &, size_t &, size_t &);
    size_t f_carry_or_borrow(size_t &);

public:
    Time(size_t, size_t, size_t, size_t);
    Time(const Time &time) : hour(time.hour), minute(time.minute), second(time.second), carry_or_borrow(time.carry_or_borrow) {}
    Time(Time &&) noexcept;
    Time &operator=(const Time &) &;
    Time &operator=(Time &&) &noexcept;
    ~Time() = default;
    size_t getHour() const { return hour; }
    void Time::setHour(const size_t &h) { hour = (h > 0 && h < 24) ? h : 0; }
    void setHour(size_t &&);
    size_t getMinute() const { return minute; }
    void setMinute(const size_t &m) { minute = (m > 0 && m <= 60) ? m : 0; }
    void setMinute(size_t &&);
    size_t getSecond() const { return second; }
    void setSecond(const size_t &s) { second = (s > 0 && s <= 60) ? s : 0; }
    void setSecond(size_t &&);
    size_t getCarryOrBorrow() const { return carry_or_borrow; }
    void setCarryOrBorrow(const size_t &c_or_b) { carry_or_borrow = c_or_b; }
    void setCarryOrBorrow(size_t &&);
    Time getCurrTime() const { return *this; }
    constexpr bool isTheSameHour(const Time &time) const { return hour == time.hour; }
    constexpr bool isTheSameMinute(const Time &time) const { return isTheSameHour(time) && minute == time.minute; }
    constexpr bool isTheSameTime(const Time &time) const { return hour == time.hour && minute == time.minute && second == time.second; }
    constexpr bool operator<(const Time &time) const
    {
        return hour < time.hour || (isTheSameHour(time) && minute < time.minute) || (isTheSameMinute(time) && second < time.second);
    }
    Time operator+(const Time &);
    Time operator+(size_t);
    Time &operator+=(const Time &) &;
    Time operator-(const Time &);
    Time operator-(size_t);
    Time &operator-=(const Time &) &;
};

inline void Time::operatorPlus(size_t &h, size_t &m, size_t &s, size_t &carry)
{
    if (s >= 60)
    {
        m += s / 60;
        if (m >= 60)
        {
            h += m / 60;
            m %= 60;
            if (h > 24)
            {
                h /= 24;
                carry = h;
            }
        }
        s %= 60;
    }
}

inline void Time::operatorMinus(size_t &h, size_t &m, size_t &s, size_t &borrow)
{
    if (s < 0)
    {
        s += 60;
        m -= 1;
        if (m < 0)
        {
            m += 60;
            h -= 1;
            borrow = 1;
        }
    }
}

Time::Time(size_t h = 0, size_t m = 0, size_t s = 0, size_t c_or_b = 0)
{
    hour = (h > 0 && h < 24) ? h : 0;
    minute = (m > 0 && m <= 60) ? m : 0;
    second = (s > 0 && s <= 60) ? s : 0;
    carry_or_borrow = c_or_b;
}

Time::Time(Time &&time) noexcept : hour(time.hour), minute(time.minute), second(time.second), carry_or_borrow(time.carry_or_borrow)
{
    time.hour = 0;
    time.minute = 0;
    time.second = 0;
    time.carry_or_borrow = 0;
}

Time &Time::operator=(const Time &rhs) &
{
    if (this != &rhs)
    {
        hour = rhs.hour;
        minute = rhs.minute;
        second = rhs.second;
        carry_or_borrow = rhs.carry_or_borrow;
    }
    return *this;
}

Time &Time::operator=(Time &&rhs) &noexcept
{
    if (this != &rhs)
    {
        hour = rhs.hour;
        minute = rhs.minute;
        second = rhs.second;
        carry_or_borrow = rhs.carry_or_borrow;
        rhs.hour = 0;
        rhs.minute = 0;
        rhs.second = 0;
        rhs.carry_or_borrow = 0;
    }
    return *this;
}

void Time::setHour(size_t &&h)
{
    hour = (h > 0 && h < 24) ? h : 0;
    h = 0;
}

void Time::setMinute(size_t &&m)
{
    minute = (m > 0 && m <= 60) ? m : 0;
    m = 0;
}

void Time::setSecond(size_t &&s)
{
    second = (s > 0 && s <= 60) ? s : 0;
    s = 0;
}

void Time::setCarryOrBorrow(size_t &&c_or_b)
{
    carry_or_borrow = c_or_b;
    c_or_b = 0;
}

Time Time::operator+(const Time &rhs)
{
    size_t h = hour + rhs.hour;
    size_t m = minute + rhs.minute;
    size_t s = second + rhs.second;
    size_t c;
    operatorPlus(h, m, s, c);
    return Time(h, m, s, c);
}

Time Time::operator+(size_t sec)
{
    size_t h = hour;
    size_t m = minute;
    size_t s = second + sec;
    size_t c;
    operatorPlus(h, m, s, c);
    return Time(h, m, s, c);
}

Time &Time::operator+=(const Time &rhs) &
{
    hour += rhs.hour;
    minute += rhs.minute;
    second += rhs.second;
    size_t c;
    operatorPlus(hour, minute, second, c);
    carry_or_borrow = c;
    return *this;
}

Time Time::operator-(const Time &rhs)
{
    if (rhs < *this)
    {
        size_t h = hour - rhs.hour;
        size_t m = minute - rhs.minute;
        size_t s = second - rhs.second;
        size_t b;
        operatorMinus(h, m, s, b);
        return Time(h, m, s, b);
    }
}

Time Time::operator-(size_t sec)
{
    size_t h = hour;
    size_t m = minute;
    size_t s = second - sec;
    size_t b;
    operatorMinus(h, m, s, b);
    return Time(h, m, s, b);
}

Time &Time::operator-=(const Time &rhs) &
{
    if (rhs < *this)
    {
        hour -= rhs.hour;
        minute -= rhs.minute;
        second -= rhs.second;
        size_t b;
        operatorMinus(hour, minute, second, b);
        carry_or_borrow = b;
        return *this;
    }
}

class Date
{
private:
    size_t year;
    size_t month;
    size_t day;
    size_t allDaysYear;
    Time time;

    static constexpr size_t ALL_DAYS_LEAP_YEAY = 366;
    static constexpr size_t ALL_DAYS_YEAY = 365;
    static constexpr size_t ALL_DAYS_FEB_LEAP_YEAY = 29;
    static constexpr size_t ALL_DAYS_FEB_YEAY = 28;
    static constexpr size_t ALL_DAYS_MONTH_31 = 31;
    static constexpr size_t ALL_DAYS_MONTH_30 = 30;

private:
    void operatorPlus(size_t &, size_t &, size_t &);
    void operatorMinus(size_t &, size_t &, size_t &);

public:
    Date() : year(1970), month(1), day(1), allDaysYear(ALL_DAYS_YEAY), time(Time()) {}
    Date(size_t, size_t, size_t, const Time &);
    Date(size_t, size_t);
    Date(const Date &date)
        : year(date.year), month(date.month), day(date.day), allDaysYear(date.allDaysYear), time(date.time) {}
    Date(Date &&date) noexcept;
    Date &operator=(const Date &) &;
    Date &operator=(Date &&) &noexcept;
    ~Date() = default;
    size_t getYear() const { return year; }
    void setYear(const size_t &y) { year = y > 1970 ? y : 1970; }
    void setYear(size_t &&);
    size_t getMonth() const { return month; }
    void setMonth(const size_t &m) { month = (m > 1 && m <= 12) ? m : 1; }
    void setMonth(size_t &&);
    size_t getDay() const { return day; }
    void setDay(const size_t &);
    void setDay(size_t &&);
    Date getCurrDate() const { return *this; }
    constexpr size_t getAllDaysYear() const { return isLeapYear() ? ALL_DAYS_LEAP_YEAY : ALL_DAYS_YEAY; };
    constexpr size_t getAllDaysMonth() const;
    constexpr bool isLeapYear() const;
    constexpr bool isTheSameYear(const Date &date) const { return year == date.year; }
    constexpr bool isTheSameMonth(const Date &date) const { return isTheSameYear(date) && month == date.month; }
    constexpr bool isTheSameDay(const Date &date) const { return isTheSameMonth(date) && day == date.day; }
    constexpr bool isTheSameTime(const Date &date) const { return isTheSameDay(date) && time.isTheSameTime(date.time); }
    constexpr bool operator<(const Date &rhs) const
    {
        return year < rhs.year || (isTheSameYear(rhs) && month < rhs.month) || (isTheSameMonth(rhs) && day < rhs.day);
    }
    Date operator+(const Date &);
    Date operator+(size_t);
    Date &operator+=(const Date &) &;
    Date operator-(const Date &);
    Date operator-(size_t);
    Date &operator-=(const Date &) &;
};

inline void Date::operatorPlus(size_t &y, size_t &m, size_t &d)
{
    size_t h, mi, s, c;
    time.operatorPlus(h, mi, s, c);
    if (m == 2)
    {
        if (isLeapYear())
            if (d > 29)
            {
                m += 1;
            }
            else
                day = (d > 1 && d <= ALL_DAYS_FEB_YEAY) ? d : 1;
    }
    else if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
        day = (d > 1 && d <= ALL_DAYS_MONTH_31) ? d : 1;
    else
        day = (d > 1 && d <= ALL_DAYS_MONTH_30) ? d : 1;
}

inline void Date::operatorMinus(size_t &y, size_t &m, size_t &d)
{
    size_t h, mi, s, b;
    time.operatorPlus(h, mi, s, b);
}

Date::Date(size_t y, size_t m, size_t d, const Time &t) : time(t)
{
    year = y > 1970 ? y : 1970;
    month = (m > 1 && m <= 12) ? m : 1;
    if (m == 2)
    {
        if (isLeapYear())
            day = (d > 1 && d <= ALL_DAYS_FEB_LEAP_YEAY) ? d : 1;
        else
            day = (d > 1 && d <= ALL_DAYS_FEB_YEAY) ? d : 1;
    }
    else if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
        day = (d > 1 && d <= ALL_DAYS_MONTH_31) ? d : 1;
    else
        day = (d > 1 && d <= ALL_DAYS_MONTH_30) ? d : 1;
    if (isLeapYear())
        allDaysYear = ALL_DAYS_LEAP_YEAY;
    else
        allDaysYear = ALL_DAYS_YEAY;
}

Date::Date(size_t m, size_t d) : year(1970), time(Time()), allDaysYear(ALL_DAYS_YEAY)
{
    month = (m > 1 && m <= 12) ? m : 1;
    if (m == 2)
    {
        if (isLeapYear())
            day = (d > 1 && d <= ALL_DAYS_FEB_LEAP_YEAY) ? d : 1;
        else
            day = (d > 1 && d <= ALL_DAYS_FEB_YEAY) ? d : 1;
    }
    else if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
        day = (d > 1 && d <= ALL_DAYS_MONTH_31) ? d : 1;
    else
        day = (d > 1 && d <= ALL_DAYS_MONTH_30) ? d : 1;
};

Date::Date(Date &&date) noexcept
    : year(date.year), month(date.month), day(date.day), allDaysYear(date.allDaysYear), time(date.time)
{
    date.year = 1970;
    date.month = 1;
    date.day = 1;
    date.time.setHour(1);
    date.time.setMinute(0);
    date.time.setSecond(0);
}

Date &Date::operator=(const Date &rhs) &
{
    if (this != &rhs)
    {
        year = rhs.year;
        month = rhs.month;
        day = rhs.day;
        time.setHour(rhs.time.getHour());
        time.setMinute(rhs.time.getMinute());
        time.setSecond(rhs.time.getSecond());
        allDaysYear = rhs.allDaysYear;
    }
    return *this;
}

Date &Date::operator=(Date &&rhs) &noexcept
{
    if (this != &rhs)
    {
        year = rhs.year;
        month = rhs.month;
        day = rhs.day;
        time.setHour(rhs.time.getHour());
        time.setMinute(rhs.time.getMinute());
        time.setSecond(rhs.time.getSecond());
        allDaysYear = rhs.allDaysYear;
        rhs.year = 1970;
        rhs.month = 1;
        rhs.day = 1;
        rhs.time.setHour(1);
        rhs.time.setMinute(0);
        rhs.time.setSecond(0);
        rhs.allDaysYear = ALL_DAYS_YEAY;
    }

    return *this;
}

void Date::setYear(size_t &&y)
{
    year = y > 1970 ? y : 1970;
    y = 1970;
}

void Date::setMonth(size_t &&m)
{
    month = (m > 1 && m <= 12) ? m : 1;
    m = 1;
}

void Date::setDay(const size_t &d)
{
    if (month == 2)
    {
        if (isLeapYear())
            day = (d > 1 && d <= ALL_DAYS_FEB_LEAP_YEAY) ? d : 1;
        else
            day = (d > 1 && d <= ALL_DAYS_FEB_YEAY) ? d : 1;
    }
    else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        day = (d > 1 && d <= ALL_DAYS_MONTH_31) ? d : 1;
    else
        day = (d > 1 && d <= ALL_DAYS_MONTH_30) ? d : 1;
}

void Date::setDay(size_t &&d)
{
    if (month == 2)
    {
        if (isLeapYear())
            day = (d > 1 && d <= ALL_DAYS_FEB_LEAP_YEAY) ? d : 1;
        else
            day = (d > 1 && d <= ALL_DAYS_FEB_YEAY) ? d : 1;
    }
    else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        day = (d > 1 && d <= ALL_DAYS_MONTH_31) ? d : 1;
    else
        day = (d > 1 && d <= ALL_DAYS_MONTH_30) ? d : 1;
    d = 1;
}

constexpr size_t Date::getAllDaysMonth() const
{
    if (month == 2)
    {
        if (isLeapYear())
            return ALL_DAYS_FEB_LEAP_YEAY;
        else
            return ALL_DAYS_FEB_YEAY;
    }
    else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        return ALL_DAYS_MONTH_31;
    else
        return ALL_DAYS_MONTH_30;
}

constexpr bool Date::isLeapYear() const
{
    return ((year & 3) == 0 && year % 100 != 0) || year % 400 == 0;
}

Date Date::operator+(const Date &rhs)
{
    Time t = time + rhs.time;
    return;
}

Date Date::operator+(size_t day)
{
    return;
}

Date &Date::operator+=(const Date &rhs) &
{
    return;
}

Date Date::operator-(const Date &)
{
    return;
}

Date Date::operator-(size_t)
{
    return;
}

Date &Date::operator-=(const Date &) &
{
    return;
}

int main(int argc, char const *argv[])
{
    Date date1;
    std::cout << date1.getDay();

    return 0;
}
