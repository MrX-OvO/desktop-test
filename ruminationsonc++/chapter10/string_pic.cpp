#include <cstring>

#include "string_pic.h"
#include "picture.h"

namespace chapter10_space
{
    String_Pic::String_Pic(const std::string str[], int n) : data(new char *[n]), size(n)
    {
        for (int i = 0; i < n; ++i)
        {
            data[i] = new char[str[i].length() + 1];
            strcpy(data[i], str[i].c_str());
        }
    }

    String_Pic::~String_Pic()
    {
        for (int i = 0; i < size; ++i)
            delete[] data[i];
        delete[] data;
    }

    int String_Pic::height() const { return size; }

    int String_Pic::width() const
    {
        int w = 0;
        for (size_t i = 0; i < size; ++i)
            w = max(w, strlen(data[i]));
        return w;
    }

    void String_Pic::display(std::ostream &os, int row, int col) const
    {
        int start = 0;
        if (row >= 0 && row < height())
        {
            os << data[row];
            start = strlen(data[row]);
        }
        pad(os, start, col);
    }

    /*  Picture String_Pic::reframe(char, char, char)
    {
        ++use;
        return this;
    }
 */
    void String_Pic::pad(std::ostream &os, int x, int y)
    {
        for (size_t i = x; i < y; ++i)
            os << " ";
    }
} // namespace