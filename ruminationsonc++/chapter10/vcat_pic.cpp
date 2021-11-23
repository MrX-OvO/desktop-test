#include "vcat_pic.h"

namespace chapter10_space
{
    Picture operator&(const Picture &t, const Picture &b) { return new VCat_Pic(t, b); }

    VCat_Pic::VCat_Pic(const Picture &t, const Picture &b) : top(t), bottom(b) {}

    int VCat_Pic::height() const { return top.height() + bottom.height(); }

    int VCat_Pic::width() const { return max(top.width(), bottom.width()); }

    void VCat_Pic::display(std::ostream &os, int row, int col) const
    {
        if (row >= 0 && row < top.height())
            top.display(os, row, col);
        else if (row < top.height() + bottom.height())
            bottom.display(os, row - top.height(), col);
        else
            pad(os, 0, col);
    }

    //Picture VCat_Pic::reframe(char c, char s, char t) { return new VCat_Pic(refframe(top, c, s, t), refframe(bottom, c, s, t)); }

    void VCat_Pic::pad(std::ostream &os, int x, int y)
    {
        for (size_t i = x; i < y; ++i)
            os << " ";
    }
} // namespace