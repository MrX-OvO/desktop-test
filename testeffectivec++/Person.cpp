#include <ostream>
#include "Person.h"

Person::Person(const std::string name, const Date &date, const std::string &addr) : pImpl(new PersonImpl(name, date, addr)) {}

Person::~Person() {}

std::string Person::getName() const { return pImpl->getName(); }

std::string Person::getBirthdate() const { return pImpl->getBirthdate(); }

std::string Person::getAddr() const { return pImpl->getAddr(); }

std::ostream &operator<<(std::ostream &os, const Person &p)
{
    os << "name: " << p.pImpl->getName() << "\nbirthdate: " << p.pImpl->getBirthdate() << "\naddr: " << p.pImpl->getAddr();
    return os;
}