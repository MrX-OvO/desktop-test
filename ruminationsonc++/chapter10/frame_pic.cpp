#include "frame_pic.h"

namespace chapter10_space
{
    Picture frame(const Picture &pic) { return new Frame_Pic(pic); }

    Frame_Pic::Frame_Pic(const Picture &pic, char c, char s, char t) : p(pic), corner(c), sideborder(s), topborder(t) {}

    int Frame_Pic::height() const { return p.height() + 2; }

    int Frame_Pic::width() const { return p.width() + 2; }

    void Frame_Pic::display(std::ostream &os, int row, int col) const
    {
        if (row < 0 || row >= height())
            // 越界
            pad(os, 0, col);
        else
        {
            // 顶框和底框
            if (row == 0 || row == height() - 1)
            {
                os << corner;
                int i = p.width();
                while (--i >= 0)
                    os << topborder;
                os << corner;
            }
            else // 内部行
            {
                os << sideborder;
                p.display(os, row - 1, p.width());
                os << sideborder;
            }
            pad(os, width(), col);
        }
    }

    // Picture Frame_Pic::reframe(char c, char s, char t) { return new Frame_Pic(refframe(p, c, s, t), c, s, t); }

    void Frame_Pic::pad(std::ostream &os, int x, int y)
    {
        for (size_t i = x; i < y; ++i)
            os << " ";
    }
} // namespace