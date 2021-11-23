#include "hcat_pic.h"

namespace chapter10_space
{
    Picture operator|(const Picture &l, const Picture &r) { return new HCat_Pic(l, r); }

    HCat_Pic::HCat_Pic(const Picture &l, const Picture &r) : left(l), right(r) {}

    int HCat_Pic::height() const { return max(left.height(), right.height()); }

    int HCat_Pic::width() const { return left.width() + right.width(); }

    void HCat_Pic::display(std::ostream &os, int row, int col) const
    {
        left.display(os, row, left.width());
        right.display(os, row, right.width());
        pad(os, width(), col);
    }

    //  Picture HCat_Pic::reframe(char c, char s, char t) { return new HCat_Pic(refframe(left, c, s, t), refframe(right, c, s, t)); }

    void HCat_Pic::pad(std::ostream &os, int x, int y)
    {
        for (size_t i = x; i < y; ++i)
            os << " ";
    }
} // namespace