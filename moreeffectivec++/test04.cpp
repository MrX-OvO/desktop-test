#include <iostream>

template <typename T>
class SmartPtr
{
public:
    SmartPtr(T *realPtr);
    SmartPtr(const SmartPtr &);
    SmartPtr &operator=(const SmartPtr &);
    ~SmartPtr();
    SmartPtr &operator*() const;
    SmartPtr *operator->() const;

private:
    T *pointee;
};