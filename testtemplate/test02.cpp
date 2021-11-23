template <typename elemType>
class ListItem;
template <typename elemType>
class List
{
public:
    List<elemType>();
    List<elemType>(const List<elemType> &);
    List<elemType> &operator=(const List<elemType> &);
    ~List();

    void insert(ListItem<elemType> *ptr, elemType value);

private:
    ListItem<elemType> *front, *end;
};

#include <iostream>
#include <vector>
template <typename T>
void print(const std::vector<T> &vec)
{
    using size_type = typename std::vector<T>::size_type;
    for (size_type i = 0; i < vec.size(); ++i)
        std::cout << vec.at(i) << (i == vec.size() - 1 ? "\n" : ", ");
}

template <typename T>
void print(const std::vector<T> &vec, const std::string &s)
{
    for (auto iter = vec.begin(); iter != vec.end();)
        std::cout << *iter++ << (iter == vec.end() ? "\n" : s);
}

int main(int argc, char const *argv[])
{

    print(std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}));
    print(std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}), ";;");

    return 0;
}
