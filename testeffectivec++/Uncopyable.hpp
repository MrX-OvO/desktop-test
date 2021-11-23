#ifndef _UNCOPYABLE_H_
#define _UNCOPYABLE_H_
class Uncopyable
{
private:
    Uncopyable(const Uncopyable &);
    Uncopyable &operator=(const Uncopyable &);

protected:
    Uncopyable() = default;
    ~Uncopyable() = default;
};
#endif // ! _UNCOPYABLE_H_