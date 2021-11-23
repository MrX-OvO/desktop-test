#include <iostream>

#ifndef _PICTURE_H
#define _PICTURE_H 1

namespace chapter10_space
{
    class P_Node;
    class Picture
    {
        friend std::ostream &operator<<(std::ostream &, const Picture &); // 重载oprator<<
        friend Picture frame(const Picture &);                            // 给图像加边框
        friend Picture refframe(const Picture &, char, char, char);       // 给图像换边框
        friend Picture operator|(const Picture &, const Picture &);       // 横向连接图像
        friend Picture operator&(const Picture &, const Picture &);       // 纵向连接图像

        friend class String_Pic;
        friend class Frame_Pic;
        friend class HCat_Pic;
        friend class VCat_Pic;

    public:
        Picture();
        Picture(const std::string[], int);
        Picture(const Picture &);
        Picture &operator=(const Picture &) &;
        ~Picture();

    private:
        P_Node *pnode;

    private:
        Picture(P_Node *);
        int height() const;
        int width() const;
        void display(std::ostream &, int, int) const;

    private:
        char &position(int, int);                  // 返回对应位置字符的引用
        char position(int, int) const;             // 返回对应位置字符的副本（const objct）
        void init(int, int);                       // 给data分配内存
        void copyBlock(int, int, const Picture &); // 将图像内容copy到另一图像中
        void clear(int, int, int, int);            // 连接图像时将无用的单元置成空格
    };
} // namespace

#endif