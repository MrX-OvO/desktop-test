#ifndef _PERSONIMPL_H_
#define _PERSONIMPL_H_
#include <string>
#include "Date.hpp"
class PersonImpl
{
public:
    PersonImpl(const std::string, const Date &, const std::string &);
    ~PersonImpl();
    std::string getName() const;
    std::string getBirthdate() const;
    std::string getAddr() const;

private:
    std::string name;
    Date date;
    std::string addr;
};
#endif // !_PERSONIMPL_H_