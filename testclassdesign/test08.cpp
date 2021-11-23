#include <iostream>
#include <string>

class PrintString
{
private:
    std::ostream &os;
    char sep;

public:
    PrintString(std::ostream &o = std::cout, char c = ' ') : os(o), sep(c) {}
    ~PrintString() = default;
    void operator()(const std::string &s) const { os << s << sep; }
    // void operator()(const char *s) const { os << s << sep; }
    //void operator()(const char s[]) const { os << s << sep; }
};

int main(int argc, char const *argv[])
{
    PrintString printer;
    std::string str = {"std::string"};
    const char *s1 = "const char*";
    const char s2[] = "const char[]";
    // printer(str);
    PrintString errors(std::cerr, '\n');
    errors(str);

    return 0;
}
