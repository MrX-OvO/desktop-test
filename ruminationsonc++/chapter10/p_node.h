#include <iostream>

#ifndef _P_NODE
#define _P_NODE

namespace chapter10_space
{
    class P_Node
    {
        friend class Picture;
        //friend Picture refframe(char, char, char);

    protected:
        int use;

    protected:
        P_Node() : use(1) {}
        virtual ~P_Node() {}
        virtual int height() const = 0;
        virtual int width() const = 0;
        virtual void display(std::ostream &, int, int) const = 0;
        //virtual Picture reframe(char, char, char) = 0;

        int max(int x, int y) const { return x > y ? x : y; }
    };
} // namespace

#endif
