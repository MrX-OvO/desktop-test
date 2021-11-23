#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

class StrCount
{
private:
    size_t len;
    static std::map<size_t, size_t> countMap;

public:
    StrCount(size_t l = 0) : len(l) {}
    ~StrCount() = default;
    void countString(std::ifstream &);
    static std::map<size_t, size_t> getCountMap() { return countMap; }
};

void StrCount::countString(std::ifstream &is)
{
    std::string line;
    while (getline(is, line))
    {
        std::istringstream stream(line);
        std::string word;
        while (stream >> word)
        {
            /* if (countMap.find(word.size()) != countMap.end())
                countMap[word.size()]++;
            else
                countMap[word.size()] = 0; */
            if (len == word.size())
                countMap[word.size()]++;
            else
                countMap[word.size()] = 0;
        }
    }
}

std::map<size_t, size_t> StrCount::countMap;

int main(int argc, char const *argv[])
{
    /*     StrCount strCount;
    std::string filePath = "./test09.txt";
    std::ifstream file(filePath);
    strCount.countString(file);
    auto map = StrCount::getCountMap();
    std::cout << "map:\n{ ";
    for (auto iter = map.begin(); iter != map.end(); ++iter)
        std::cout << "{ " << iter->first << " : " << iter->second << (iter == --map.end() ? " }" : " }, ");
    std::cout << " }\n"; */

    std::string filePath = "./test09.txt";
    std::ifstream file(filePath);
    for (size_t i = 1; i <= 10; ++i)
    {
        StrCount strCount(i);
        strCount.countString(file);
    }
    auto map = StrCount::getCountMap();
    std::cout << "map:\n{ ";
    for (auto iter = map.begin(); iter != map.end(); ++iter)
        std::cout << "{ " << iter->first << " : " << iter->second << (iter == --map.end() ? " }" : " }, ");
    std::cout << " }\n";

    return 0;
}
