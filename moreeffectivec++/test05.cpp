#include <cstring>

class RCObject
{
public:
    void addReference();
    void removeReference();
    void markUnshareable();
    bool isShareable() const;
    bool isShared() const;

protected:
    RCObject();
    RCObject(const RCObject &);
    RCObject &operator=(const RCObject &) &;
    virtual ~RCObject() = 0;

private:
    size_t refCount;
    bool shareable;
};

RCObject::RCObject() : refCount(0), shareable(true) {}

RCObject::RCObject(const RCObject &) : refCount(0), shareable(true) {}

RCObject &RCObject::operator=(const RCObject &) & { return *this; }

RCObject::~RCObject() {}

void RCObject::addReference() { ++refCount; }

void RCObject::removeReference()
{
    if (--refCount == 0)
        delete this;
}

void RCObject::markUnshareable() { shareable = false; }

bool RCObject::isShareable() const { return shareable; }

bool RCObject::isShared() const { return refCount > 1; }

template <typename T> // T必须支持RCObject接口，因此T通常继承自RCObject
class RCPtr
{
public:
    RCPtr(T *);
    RCPtr(const RCPtr &);
    RCPtr &operator=(const RCPtr &) &;
    ~RCPtr();

    T &operator*() const;
    T *operator->() const;

private:
    T *pointee;
    void init();
};

template <typename T>
void RCPtr<T>::init()
{
    if (pointee == nullptr)
        return;
    if (pointee->isShareable() == false)
        pointee = new T(*pointee); // 调用copy constructor，但该class没有定义它，故用编译器默认生成的，进行浅复制（复制指针）
                                   // 要实现深复制，就要在用到RCPtr的class中实现拷贝构造
    pointee->addReference();
}

template <typename T>
RCPtr<T>::RCPtr(T *realPtr = nullptr) : pointee(realPtr) { init(); }

template <typename T>
RCPtr<T>::RCPtr(const RCPtr &rcPtr) : pointee(rcPtr.pointee) { init(); }

template <typename T>
RCPtr<T> &RCPtr<T>::operator=(const RCPtr &rhs) &
{
    if (pointee != rhs.pointee)
    {
        if (pointee)
            pointee->removeReference();
        pointee = rhs.pointee;
        init();
    }
    return *this;
}

template <typename T>
RCPtr<T>::~RCPtr()
{
    if (pointee)
        pointee->removeReference();
}

template <typename T>
T &RCPtr<T>::operator*() const { return *pointee; }

template <typename T>
T *RCPtr<T>::operator->() const { return &this->operator*(); }

class MyString
{
public:
    MyString(const char *);

    const char &operator[](int) const &;
    char &operator[](int) &;

private:
    struct MyStringValue : public RCObject
    {
        char *data;

        MyStringValue(const char *);
        MyStringValue(const MyStringValue &);
        ~MyStringValue();
        void init(const char *);
    };
    RCPtr<MyStringValue> value;
};

void MyString::MyStringValue::init(const char *initValue)
{
    data = new char[strlen(initValue) + 1];
    strcpy(data, initValue);
}

MyString::MyStringValue::MyStringValue(const char *initValue) { init(initValue); }

MyString::MyStringValue::MyStringValue(const MyStringValue &myStrVal) { init(myStrVal.data); }

MyString::MyStringValue::~MyStringValue() { delete[] data; }

MyString::MyString(const char *initValue = " ") : value(new MyStringValue(initValue)) {}

const char &MyString::operator[](int index) const & { return value->data[index]; }

char &MyString::operator[](int index) &
{
    if (value->isShared())
        value->markUnshareable(); // 如果已共享，则先复制一份
    value->removeReference();
    value = new MyStringValue(value->data);
    return value->data[index];
}

template <typename T>
class RCIPtr
{
public:
    RCIPtr(T *realPtr);
    RCIPtr(const RCIPtr &);
    RCIPtr &operator=(const RCIPtr &) &;
    ~RCIPtr();
    const T &operator*() const;
    T &operator*();
    const T *operator->() const;
    T *operator->();

private:
    struct CountHolder : public RCObject
    {
        T *pointee;
        ~CountHolder() { delete pointee; }
    };
    CountHolder *counter;
    void init();
    void makeCopy();
};

template <typename T>
void RCIPtr<T>::init()
{
    if (counter->isShareable() == false)
    {
        T *oldValue = counter->pointee;
        counter = new CountHolder;
        counter->pointee = new T(*oldValue);
    }
    counter->addReference();
}

template <typename T>
RCIPtr<T>::RCIPtr(T *realPtr = nullptr) : counter(new CountHolder)
{
    counter->pointee = realPtr;
    init();
}

template <typename T>
RCIPtr<T>::RCIPtr(const RCIPtr &rciPtr) : counter(rciPtr.counter) { init(); }

template <typename T>
RCIPtr<T> &RCIPtr<T>::operator=(const RCIPtr &rhs) &
{
    if (counter != rhs.counter)
    {
        counter->removeReference();
        counter = rhs.counter;
        init();
    }
    return *this;
}

template <typename T>
RCIPtr<T>::~RCIPtr() { counter->removeReference(); }

template <typename T>
const T &RCIPtr<T>::operator*() const { return *(counter->pointee); }

template <typename T>
T &RCIPtr<T>::operator*() {}

template <typename T>
const T *RCIPtr<T>::operator->() const { return &this->operator*(); }

template <typename T>
T *RCIPtr<T>::operator->() {}

class Widget
{
public:
    Widget(unsigned);
    Widget(const Widget &);
    Widget &operator=(const Widget) &;
    ~Widget();

    void doThis();
    int showWhat() const;

private:
    unsigned size;
};

class RCWidget
{
public:
    RCWidget(unsigned size) : value(new Widget(size)) {}

    void doThis() { value->doThis(); }
    int showWhat() const { value->showWhat(); }

private:
    RCIPtr<Widget> value;
};
