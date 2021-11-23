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
    unsigned refCount;
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

    class CharProxy
    {
    public:
        CharProxy(MyString &str, unsigned index) : theString(str), charIndex(index) {}
        CharProxy &operator=(const CharProxy &) &;
        CharProxy &operator=(char) &;

        operator char() const { return theString.value->data[charIndex]; }

        const char *operator&() const { return &(theString.value->data[charIndex]); }

        char *operator&()
        {
            makeCopy();
            theString.value->markUnshareable();
            return const_cast<char *>(&static_cast<const CharProxy &>(*this));
        }

    private:
        MyString &theString;
        unsigned charIndex;

    private:
        void makeCopy();
    };

    const CharProxy operator[](unsigned) const;
    CharProxy operator[](unsigned);

    friend class CharProxy;

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

void MyString::CharProxy::makeCopy()
{
    if (theString.value->isShared())
        theString.value = new MyStringValue(theString.value->data);
}

const MyString::CharProxy MyString::operator[](unsigned index) const { return CharProxy(const_cast<MyString &>(*this), index); }

MyString::CharProxy MyString::operator[](unsigned index) { return CharProxy(*this, index); }

MyString::CharProxy &MyString::CharProxy::operator=(const CharProxy &rhs) &
{
    makeCopy();
    theString.value->data[charIndex] = rhs.theString.value->data[rhs.charIndex];
    return *this;
}

MyString::CharProxy &MyString::CharProxy::operator=(char c) &
{
    makeCopy();
    theString.value->data[charIndex] = c;
    return *this;
}
