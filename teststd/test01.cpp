#include <iostream>
#include <string>
#include <regex>

void find_c_like_file(const std::string &files)
{
    try
    {
        std::regex r("([[:alnum:]]+)\\.(cpp|cxx|cc)$", std::regex::icase);
        std::cmatch results;
        if (std::regex_search("x.CC test.txt abc.cpp x.html z.cXx b.javac d.py e.js ", results, r))
            std::cout << results.str() << std::endl;
        for (std::sregex_iterator iter(files.begin(), files.end(), r), end_iter; iter != end_iter; ++iter)
            std::cout << iter->str() << std::endl;
    }
    catch (const std::regex_error &e)
    {
        std::cerr << e.what() << "\ncode: " << e.code() << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    std::string files = "x.CC test.txt abc.cpp x.html z.cXx b.javac d.py e.js ";
    find_c_like_file(files);

    return 0;
}
