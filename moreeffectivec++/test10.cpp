namespace auto_ptr_space
{
    template <typename T>
    class AutoPtr
    {

    public:
        explicit AutoPtr(T *p = nullptr);
        template <typename U>
        AutoPtr(AutoPtr<U> &);
        ~AutoPtr();

        template <typename U>
        AutoPtr<T> &operator=(AutoPtr<U> &) &;
        T &operator*() const;
        T *operator->() const;

        T *get() const;
        T *release();
        void reset(T *p = nullptr);

    private:
        T *pointee;

        /*         template <typename U>
        friend class AutoPtr<U>; */
    };

    template <typename T>
    inline AutoPtr<T>::AutoPtr(T *p) : pointee(p) {}

    template <typename T>
    template <typename U>
    inline AutoPtr<T>::AutoPtr(AutoPtr<U> &autoPtr) : pointee(autoPtr.release()) {}

    template <typename T>
    inline AutoPtr<T>::~AutoPtr() { delete pointee; }

    template <typename T>
    template <typename U>
    inline AutoPtr<T> &AutoPtr<T>::operator=(AutoPtr<U> &rhs) &
    {
        if (this != &rhs)
            reset(rhs.release());
        return *this;
    }

    template <typename T>
    inline T &AutoPtr<T>::operator*() const { return *pointee; }

    template <typename T>
    inline T *AutoPtr<T>::operator->() const { return &this->operator*(); }

    template <typename T>
    inline T *AutoPtr<T>::get() const { return pointee; }

    template <typename T>
    inline T *AutoPtr<T>::release()
    {
        T *oldPointee = pointee;
        pointee = nullptr;
        return oldPointee;
    }

    template <typename T>
    inline void AutoPtr<T>::reset(T *p)
    {
        if (pointee != p)
        {
            delete pointee;
            pointee = p;
        }
    }
}

/* 
namespace auto_ptr_space
{
    template <>
    class AutoPtr<int>
    {

    public:
        explicit AutoPtr(int *p = nullptr) : pointee(p) {}
        template <typename U>
        AutoPtr(AutoPtr<U> &autoPtr) : pointee(autoPtr.release()) {}
        ~AutoPtr() { delete pointee; }

        template <typename U>
        AutoPtr<int> &operator=(AutoPtr<U> &rhs) &
        {
            if (this != &rhs)
                reset(rhs.release());
            return *this;
        }
        int &operator*() const { return *pointee; }
        int *operator->() const { return &this->operator*(); }

        int *get() const { return pointee; }
        int *release()
        {
            int *oldPointee = pointee;
            pointee = nullptr;
            return oldPointee;
        }
        void reset(int *p = nullptr)
        {
            if (pointee != p)
            {
                delete pointee;
                pointee = p;
            }
        }

    private:
        int *pointee;
    };
} */

#include <iostream>
#include <utility> // std::pair
#include <cmath>

namespace
{
    struct MyStruct
    {
        int i;
        double d;
        void setValue(int ivalue = 0, double dvalue = 0.0)
        {
            i = ivalue;
            d = dvalue;
        }
        std::pair<int, double> getValue() const { return std::make_pair(i, d); }
        void printValue() { std::cout << "MyStruct i = " << i << ", MyStruct d = " << d << std::endl; }
    };

    std::ostream &operator<<(std::ostream &os, const MyStruct &myStruct)
    {
        os << "{int i = " << myStruct.i << ", double d = " << std::showpoint << myStruct.d << "}\n";
        return os;
    }
}

int main(int argc, char const *argv[])
{

    auto_ptr_space::AutoPtr<MyStruct> autoPtrMyStruct(new MyStruct);
    std::cout << "*autoPtrMyStruct = " << *autoPtrMyStruct;
    std::cout << "autoPtrMyStruct->getValue().first = " << autoPtrMyStruct->getValue().first
              << ", autoPtrMyStruct->getValue().second = " << autoPtrMyStruct->getValue().second << std::endl;
    autoPtrMyStruct->setValue(2, sqrt(2.0));
    std::cout << "after setValue(2, sqrt(2.0))...\n";
    autoPtrMyStruct->printValue();
    std::cout << "autoPtrMyStruct->getValue().first = " << autoPtrMyStruct->getValue().first
              << ", autoPtrMyStruct->getValue().second = " << autoPtrMyStruct->getValue().second << std::endl;
    std::cout << "*autoPtrMyStruct = " << *autoPtrMyStruct;

    return 0;
}
