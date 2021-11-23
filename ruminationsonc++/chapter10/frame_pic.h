#include "p_node.h"
#include "picture.h"

#ifndef _FRAME_NODE
#define _FRAME_NODE

namespace chapter10_space
{
    class Frame_Pic : public P_Node
    {
        friend Picture frame(const Picture &);

        Picture p;
        char corner;
        char sideborder;
        char topborder;

        Frame_Pic(const Picture &, char = '+', char = '|', char = '-');

        int height() const override;
        int width() const override;
        void display(std::ostream &, int, int) const override;
        // Picture reframe(char, char, char) override;

        static void pad(std::ostream &, int, int);
    };
} // namespace

#endif