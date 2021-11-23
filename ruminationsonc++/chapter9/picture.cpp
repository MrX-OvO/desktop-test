#include <cassert>

#include "picture.h"

namespace chapter9_space
{

    char &Picture::position(size_t row, size_t col) { return data[row * width + col]; }

    char Picture::position(size_t row, size_t col) const { return data[row * width + col]; }

    void Picture::init(size_t h, size_t w)
    {
        height = h;
        width = w;
        data = new char[height * width];
    }

    void Picture::copyBlock(size_t row, size_t col, const Picture &p)
    {
        // assert((row >= 0 && row < p.height) || (col > 0 && col < p.width));
        for (size_t i = 0; i < p.height; ++i)
            for (size_t j = 0; j < p.width; ++j)
                // 将图像p复制到当前图像(row,col)位置
                position(i + row, j + col) = p.position(i, j);
    }

    void Picture::clear(size_t r1, size_t c1, size_t r2, size_t c2)
    {
        for (size_t r = r1; r < r2; ++r)
            for (size_t c = c1; c < c2; ++c)
                position(r, c) = ' ';
    }

    Picture::Picture() : height(0), width(0), data(nullptr) {}

    Picture::Picture(const std::string array[], size_t h)
    {
        // 计算（最大）宽度
        size_t w = 0;
        for (size_t i = 0; i < h; ++i)
            w = std::max(w, array[i].length());

        // 给data分配内存
        init(h, w);

        // 将源端字符复制到data中
        for (size_t i = 0; i < h; ++i)
        {
            const std::string src = array[i];
            size_t len = array[i].length();
            size_t j = 0;
            while (j < len)
            {
                position(i, j) = src[j];
                ++j;
            }
            // 用空格补齐
            while (j < width)
            {
                position(i, j) = ' ';
                ++j;
            }
        }
    }

    Picture::Picture(const Picture &p) : height(p.height), width(p.width), data(new char[p.height, p.width]) { copyBlock(0, 0, p); }

    Picture &Picture::operator=(const Picture &rhs) &
    {
        if (this != &rhs)
        {
            delete[] data;
            init(rhs.height, rhs.width);
            copyBlock(0, 0, rhs);
        }
        return *this;
    }

    Picture::~Picture()
    {
        delete[] data;
    }

    std::ostream &operator<<(std::ostream &os, const Picture &p)
    {
        for (size_t i = 0; i < p.height; ++i)
        {
            for (size_t j = 0; j < p.width; ++j)
                os << p.position(i, j);
            os << std::endl;
        }

        return os;
    }

    Picture frame(const Picture &p)
    {
        Picture r;

        // 分配内存，高度和宽度各增加2
        r.init(p.height + 2, p.width + 2);

        // 给图像左右两侧添加“|”边框
        for (size_t i = 1; i < r.height - 1; ++i)
        {
            r.position(i, 0) = '|';
            r.position(i, r.width - 1) = '|';
        }

        // 给图像上下两侧添加“+-+”边框
        // 上下边框用“-”字符
        for (size_t j = 1; j < r.width - 1; ++j)
        {
            r.position(0, j) = '-';
            r.position(r.height - 1, j) = '-';
        }
        // 4个角用“+”字符
        r.position(0, 0) = '+';
        r.position(0, r.width - 1) = '+';
        r.position(r.height - 1, 0) = '+';
        r.position(r.height - 1, r.width - 1) = '+';

        // 复制图像到位置(1,1)
        r.copyBlock(1, 1, p);

        return r;
    }

    Picture operator|(const Picture &p, const Picture &q)
    {
        Picture r;

        // 分配内存
        r.init(std::max(p.height, q.height), p.width + q.width);

        // 清空矩形的两个对角
        if (p.height < q.height)
            r.clear(p.height, 0, r.height, p.width);
        else if (p.height > q.height)
            r.clear(q.height, p.width, r.height, r.width);

        // 复制源图像
        r.copyBlock(0, 0, p);
        r.copyBlock(0, p.width, q);

        return r;
    }
    Picture operator&(const Picture &p, const Picture &q)
    {
        Picture r;

        // 分配内存
        r.init(p.height + q.height, std::max(p.width, q.width));

        // 清空矩形的两个对角
        if (p.width < q.width)
            r.clear(0, p.width, p.height, r.width);
        else if (p.width > q.width)
            r.clear(p.height, q.width, r.height, r.width);

        // 复制源图像
        r.copyBlock(0, 0, p);
        r.copyBlock(p.height, 0, q);

        return r;
    }

} // namespace