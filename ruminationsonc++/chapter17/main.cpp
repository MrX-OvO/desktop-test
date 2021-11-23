namespace test01
{
    const int *find(const int *arr, int n, int x)
    {
        const int *p = arr;
        for (int i = 0; i < n; ++i)
        {
            if (*p++ == x)
                return p;
        }
        return nullptr;
    }
} // namespace test01

namespace test02
{
    template <typename T>
    T *find(T *arr, int n, const T &x)
    {
        T *p = arr;
        for (int i = 0; i < n; ++i)
        {
            if (*p++ == x)
                return p;
        }
        return nullptr;
    }
} // namespace test02

namespace test03
{
    template <typename T>
    T *find(T *arr, T *beyond, const T &x)
    {
        T *p = arr;
        while (p != beyond)
        {
            if (*p++ == x)
                return p;
        }
        return nullptr;
    }
} // namespace test03

namespace test04
{
    template <typename T>
    T *find(T *arr, T *beyond, const T &x)
    {
        T *p = arr;
        while (p != beyond)
        {
            if (*p++ == x)
                return p;
        }
        return beyond;
    }
} // namespace test04

namespace test05
{
    template <typename T>
    T *find(T *arr, T *beyond, const T &x)
    {
        T *p = arr;
        while (p != beyond && *p++ != x)
        {
        }
        return p;
    }
} // namespace test05

namespace test06
{
    template <typename P, typename T>
    P find(P start, P beyond, const T &x)
    {
        while (start != beyond && *start++ != x)
        {
        }
        //++start;
        return start;
    }
} // namespace test06

#include <string>

namespace test07
{
    struct Node
    {
        std::string value;
        Node *next;
    };

    Node *find(Node *p, const std::string &x)
    {
        while (p && p->value != x)
            p = p->next;
        return p;
    }
} // namespace test07

#include <memory>

namespace test08
{
    using Node = test07::Node;

    class Nodep
    {
        friend bool operator==(const Nodep &, const Nodep &);
        friend bool operator!=(const Nodep &, const Nodep &);

    public:
        Nodep(Node *p) : pnode(p){};

        std::string &operator*() const { return pnode->value; }
        void operator++() { pnode = pnode->next; }
        std::shared_ptr<Node> operator++(int)
        {
            std::shared_ptr<Node> ret(new Node(*pnode));
            ++*this;
            return ret;
        }
        operator Node *() { return pnode; }

    private:
        Node *pnode;
    };

    bool operator==(const Nodep &p, const Nodep &q) { return p.pnode == q.pnode; }

    bool operator!=(const Nodep &p, const Nodep &q) { return !(p == q); }

    Node *find(Node *p, const std::string &x) { return test06::find(Nodep(p), Nodep(nullptr), x); }
} // namespace test08

#include <iostream>

int main(int argc, char const *argv[])
{
    int arr[] = {1, 2, 3, 4, 5};

    std::cout << "+=+namespace test01+=+\n";
    std::cout << "find? result: " << (test01::find(arr, 5, 1) == nullptr ? "nullptr\n" : "found\n");
    std::cout << "+=+namespace test01+=+\n";

    std::cout << "+=+namespace test02+=+\n";
    std::cout << "find? result: " << (test02::find(arr, 5, 3) == nullptr ? "nullptr\n" : "found\n");
    std::cout << "+=+namespace test02+=+\n";

    return 0;
}
