#ifndef _SEQ_H
#define _SEQ_H

namespace chapter15_space
{
    template <typename T>
    class Seq_item;
    template <typename T>
    class Seq
    {
        template <typename U>
        friend bool operator==(const Seq<U> &, const Seq<U> &);

    public:
        Seq();
        Seq(const Seq &);
        Seq &operator=(const Seq &) &;
        ~Seq();

        operator bool() const;
        Seq &operator++();
        Seq operator++(int);
        T operator*() const; // T head() const;

        Seq tail() const;
        unsigned length();
        Seq cons(const T &, const Seq &); // Seq(const T &, const Seq &);
        Seq &insert(const T &);
        Seq_item<T> *owntail();
        Seq &filp();

    private:
        Seq_item<T> *pitem;
        unsigned len;

    private:
        Seq(const T &, const Seq &);
        T head() const;
        Seq(Seq_item<T> *, unsigned l);
        void destroy(Seq_item<T> *);
    };
} // namespace

#endif