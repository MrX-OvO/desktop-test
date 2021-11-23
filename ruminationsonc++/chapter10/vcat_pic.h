#include "p_node.h"
#include "picture.h"

#ifndef _VCAT_NODE
#define _VCAT_NODE

namespace chapter10_space
{
    class VCat_Pic : public P_Node
    {
        friend Picture operator&(const Picture &, const Picture &);

        Picture top, bottom;

        VCat_Pic(const Picture &, const Picture &);

        int height() const override;
        int width() const override;
        void display(std::ostream &, int, int) const override;
        //Picture reframe(char, char, char) override;

        static void pad(std::ostream &, int, int);
    };
} // namespace

#endif