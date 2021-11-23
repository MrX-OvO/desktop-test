#ifndef _SEQ_ITEM_H
#define _SEQ_ITEM_H

namespace chapter15_space
{
    template <typename T>
    class Seq;
    template <typename T>
    class Seq_item
    {
        friend class Seq<T>;

        unsigned use;
        const T data;
        Seq_item *next;

        Seq_item(const T &);
        Seq_item(const T &, Seq_item *);
    };
} // namespace

#endif