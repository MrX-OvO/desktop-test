#include "p_node.h"

#ifndef _STRING_NODE
#define _STRING_NODE

namespace chapter10_space
{
    class String_Pic : public P_Node
    {
        friend class Picture;

        char **data;
        int size;

        String_Pic(const std::string[], int);
        ~String_Pic();

        int height() const override;
        int width() const override;
        void display(std::ostream &, int, int) const override;
        //Picture::Picture reframe(char, char, char) override;

        static void pad(std::ostream &, int, int);
    };
} // namespace

#endif