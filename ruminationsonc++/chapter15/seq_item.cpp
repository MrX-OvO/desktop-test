#include "seq_item.h"

namespace chapter15_space
{
    template <typename T>
    Seq_item<T>::Seq_item(const T &t) : use(1), data(t), next(nullptr) {}

    template <typename T>
    Seq_item<T>::Seq_item(const T &t, Seq_item *s) : use(1), data(t), next(s)
    {
        if (s)
            ++s->use;
    }
} // namespace