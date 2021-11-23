#include <iostream>
#include <string>

class Window
{
public:
    Window(const std::string &s = " ") : name(s) {}
    virtual ~Window() = default;

    std::string getName() const { return name; }
    virtual void display() const { std::cout << "Window..."; }

private:
    std::string name;
};

class WindowWithScrollBar : public Window
{
public:
    WindowWithScrollBar(const std::string &s1 = " ", const std::string &s2 = " ") : Window(s2), name(s1) {}
    virtual ~WindowWithScrollBar() = default;

    void display() const override { std::cout << "WindowWithScrollBar..."; }

private:
    std::string name;
};

#if 0
void printNameAndDisplay(Window w)
{
    std::cout << w.getName() << std::endl;
    w.display();
    std::cout << std::endl;
}
#elif 1
void printNameAndDisplay(const Window &w)
{
    std::cout << w.getName() << std::endl;
    w.display();
    std::cout << std::endl;
}
#endif

int main(int argc, char const *argv[])
{
    Window w("window1");
    WindowWithScrollBar wwsb("WindowWithScrollBar1", "window2");
    printNameAndDisplay(w);
    printNameAndDisplay(wwsb);

    return 0;
}
