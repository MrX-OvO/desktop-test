#include <cassert>

#include "seq.h"

namespace chapter15_space
{

    template <typename T>
    Seq<T>::Seq(const T &t, const Seq &s) : pitem(new Seq_item<T>(t, s.pitem)), len(s.len + 1) {}

    template <typename T>
    T Seq<T>::head() const
    {
        if (pitem)
            return pitem->data;
        else
            throw "head of an empty Seq";
    }

    template <typename T>
    Seq<T>::Seq(Seq_item<T> *s, unsigned l) : pitem(s), len(l)
    {
        if (s)
            ++s->use;
    }

    template <typename T>
    void Seq<T>::destroy(Seq_item<T> *s)
    {
        while (s && --s->use == 0)
        {
            Seq_item<T> *next = s->next;
            delete pitem;
            pitem = next;
        }
    }

    template <typename T>
    Seq<T>::Seq() : pitem(nullptr) {}

    template <typename T>
    Seq<T>::Seq(const Seq &s) : pitem(s.pitem), len(s.len)
    {
        if (pitem)
            ++pitem->use;
    }

    template <typename T>
    Seq<T> &Seq<T>::operator=(const Seq &rhs) &
    {
        if (rhs.pitem)
            ++rhs.pitem->use;
        destroy(pitem);
        pitem = rhs.pitem;
        len = rhs.len;
        return *this;
    }

    template <typename T>
    Seq<T>::~Seq() { destroy(pitem); }

    template <typename T>
    Seq<T>::operator bool() const { return pitem != nullptr; }

    template <typename T>
    Seq<T> &Seq<T>::operator++()
    {
        if (pitem)
        {
            Seq_item<T> *p = pitem->next;
            if (p)
                ++p->use;
            if (--pitem->use == 0)
                delete pitem;
            pitem = p;
        }
        return *this;
    }

    template <typename T>
    Seq<T> Seq<T>::operator++(int)
    {
        Seq ret = *this;
        if (pitem)
        {
            --pitem->use;
            pitem = pitem->next;
            if (pitem)
                ++pitem->use;
        }
        return ret;
    }

    template <typename T>
    T Seq<T>::operator*() const { return head(); }

    template <typename T>
    Seq<T> Seq<T>::tail() const
    {
        if (pitem)
            return Seq(pitem->next, len - 1);
        else
            throw "tail of an empty Seq";
    }

    template <typename T>
    unsigned Seq<T>::length() { return len; }

    template <typename T>
    Seq<T> Seq<T>::cons(const T &t, const Seq &s) { return Seq(t, s); }

    template <typename T>
    Seq<T> &Seq<T>::insert(const T &t)
    {
        pitem = new Seq_item<T>(t, pitem);
        ++len;
        return *this;
    }

    template <typename T>
    Seq_item<T> *Seq<T>::owntail()
    {
        if (pitem == nullptr)
            return nullptr;

        Seq_item<T> *i = pitem;
        Seq_item<T> **p = &pitem;

        while (i->use == 1)
        {
            if (i->newx == nullptr)
                return i;
            p = &i->next;
            i = i->next;
        }

        // i指向第一个use!=1的项
        *p = new Seq_item<T>(i->data);
        --i->use;
        i = i->next;

        Seq_item<T> j = *p;
        while (i)
        {
            j->next = new Seq_item<T>(i->data);
            i = i->next;
            j = j->next;
        }
        return j;
    }

    template <typename T>
    Seq<T> &Seq<T>::filp()
    {
        if (pitem)
        {
            Seq_item<T> *k = owntail();
            Seq_item<T> *curr = pitem;
            Seq_item<T> *behind = nullptr;

            do
            {
                Seq_item<T> *ahead = curr->next;
                curr->next = behind;
                behind = curr;
                curr = ahead;
            } while (curr);
            pitem = k;
        }
        return *this;
    }

    template <typename U>
    bool operator==(const Seq<U> &op1, const Seq<U> &op2)
    {
        if (op1.length() != op2.length())
            return false;

        Seq_item<U> *p = op1.pitem;
        Seq_item<U> *q = op2.pitem;

        while (p != q)
        {
            assert(p != nullptr && q != nullptr);
            if (*p++ != *q++)
                return false;
        }

        return true;
    }
} // namespace