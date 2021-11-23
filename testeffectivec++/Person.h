#ifndef _PERSON_H_
#define _PERSON_H_
#include <memory>
#include "PersonImpl.h"
class Person
{
    friend std::ostream &operator<<(std::ostream &, const Person &);

public:
    Person(const std::string, const Date &, const std::string &);
    ~Person();
    std::string getName() const;
    std::string getBirthdate() const;
    std::string getAddr() const;

private:
    std::shared_ptr<PersonImpl> pImpl;
};
#endif // !_PERSON_H_