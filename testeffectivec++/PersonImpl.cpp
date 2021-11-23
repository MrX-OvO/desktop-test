#include <ostream>
#include "PersonImpl.h"

PersonImpl::PersonImpl(const std::string name, const Date &date, const std::string &addr) : name(name), date(date), addr(addr) {}

PersonImpl::~PersonImpl() = default;

std::string PersonImpl::getName() const { return name; }

std::string PersonImpl::getBirthdate() const { return date.getDate(); }

std::string PersonImpl::getAddr() const { return addr; }

std::ostream &operator<<(std::ostream &os, const PersonImpl &p)
{
    os << "name: " << p.getName() << "\nbirthdate: " << p.getBirthdate() << "\naddr: " << p.getAddr();
    return os;
}