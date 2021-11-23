#include "seq.h"

#ifndef _SEQ_ALGORITHM_H
#define _SEQ_ALGORITHM_H

namespace chapter15_space
{
    template <typename T>
    Seq<T> merge(const Seq<T> &x, const Seq<T> &y)
    {
        Seq<T> r;
        // 如果一个Seq为空，则返回另一个Seq
        if (!x)
            return y;
        if (!y)
            return x;

        // 二者都不为空，分别取出它们的第一个元素
        T xh = *x;
        T yh = *y;

        // 进行比较
        /*   if (xh < yh)
        return cons(xh, merge(x.tail(), y));
        return cons(yh, merge(x, y.tail())); */
        if (xh < yh)
            r.cons(xh, merge(x.tail(), y));
        r.cons(yh, merge(x, y.tail()));
        return r;
    }

    template <typename T>
    Seq<T> merge2(const Seq<T> &x, const Seq<T> &y)
    {
        Seq<T> r;
        while (x && y)
        {
            if (*x < *y)
            {
                r.insert(*x);
                x++;
            }
            else
            {
                r.insert(*y);
                y++;
            }
        }
        while (x)
        {
            r.insert(*x);
            x++;
        }
        while (y)
        {
            r.insert(*y);
            y++;
        }
        r.filp();

        return r;
    }

    template <typename T>
    void split(Seq<T> &x, Seq<T> &y, Seq<T> &z)
    {
        while (x)
        {
            y.insert(*x);
            if (++x)
            {
                z.insert(*x);
                ++x;
            }
        }
    }

    template <typename T>
    Seq<T> sort(Seq<T> &x)
    {
        if (!x || !x.tail())
            return x;
        Seq<T> p, q;
        split<T>(x, p, q);
        return merge<T>(sort(p), sort(q));
    }
} // namespace

#endif
