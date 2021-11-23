#include "picture.h"
#include "p_node.h"
#include "string_pic.h"

namespace chapter10_space
{
    std::ostream &operator<<(std::ostream &os, const Picture &p)
    {
        int h = p.height();
        for (int i = 0; i < h; ++i)
        {
            p.display(os, i, 0);
            os << std::endl;
        }
        return os;
    }

    //Picture refframe(const Picture &p, char c, char s, char t) { return p.pnode->reframe(c, s, t); }

    Picture::Picture(P_Node *p) : pnode(p) {}

    int Picture::height() const { return pnode->height(); }

    int Picture::width() const { return pnode->width(); }

    void Picture::display(std::ostream &os, int x, int y) const { pnode->display(os, x, y); }

    Picture::Picture() {}

    Picture::Picture(const std::string str[], int n) : pnode(new String_Pic(str, n)) {}

    Picture::Picture(const Picture &p) : pnode(p.pnode) { ++p.pnode->use; }

    Picture &Picture::operator=(const Picture &rhs) &
    {
        ++rhs.pnode->use;
        if (--pnode->use == 0)
            delete pnode;
        pnode = rhs.pnode;
        return *this;
    }

    Picture::~Picture()
    {
        if (--pnode->use == 0)
            delete pnode;
    }

} // namespace