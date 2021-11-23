#include <iostream>
#include <string>

#ifndef _PICTURE_H
#define _PICTURE_H 1

namespace chapter9_space
{
    class Picture
    {
        friend std::ostream &operator<<(std::ostream &, const Picture &); // 重载oprator<<
        friend Picture frame(const Picture &);                            // 给图像加边框
        friend Picture operator|(const Picture &, const Picture &);       // 横向连接图像
        friend Picture operator&(const Picture &, const Picture &);       // 纵向连接图像

    public:
        Picture();
        Picture(const std::string[], size_t);
        Picture(const Picture &);
        Picture &operator=(const Picture &) &;
        ~Picture();

    private:
        size_t height, width;
        char *data;

    private:
        char &position(size_t, size_t);                  // 返回对应位置字符的引用
        char position(size_t, size_t) const;             // 返回对应位置字符的副本（const objct）
        void init(size_t, size_t);                       // 给data分配内存
        void copyBlock(size_t, size_t, const Picture &); // 将图像内容copy到另一图像中
        void clear(size_t, size_t, size_t, size_t);      // 连接图像时将无用的单元置成空格
    };
} // namespace

#endif