#include <iostream>
#include <string>

class ZooAnimal
{
public:
    explicit ZooAnimal(const std::string &s = " ") : name(s) {}
    virtual ~ZooAnimal() = default;
    std::string getName() const { return name; }
    virtual void print() { std::cout << "call virtual void ZooAnimal::print()\n"; }

private:
    std::string name;
};

class Bear : public ZooAnimal
{
public:
    explicit Bear(const std::string &s1 = " ", const std::string &s2 = " ") : name(s1), ZooAnimal(s2) {}
    virtual ~Bear() = default;
    std::string getName() const { return name; }
    void print() override { std::cout << "call virtual void Bear::print()\n"; }
    virtual void toes() { std::cout << "call virtual void Bear::toes()\n"; }

private:
    std::string name;
};

class Endangered
{
public:
    Endangered(bool d = false) : dangered(d) {}
    virtual ~Endangered() = default;
    bool isDangered() const { return dangered; }
    virtual void print() { std::cout << "call virtual void Endangered::print()\n"; }
    virtual void hightlight() { std::cout << "call virtual void Endangered::hightlight()\n"; }

private:
    bool dangered;
};

class Panda : public Bear, public Endangered
{
    friend std::ostream &operator<<(std::ostream &, const ZooAnimal &);

public:
    Panda(const std::string &s1 = " ", const std::string &s2 = " ", const std::string &s3 = " ", bool d = false)
        : name(s1), Bear(s2, s3), Endangered(d) {}
    ~Panda() = default;
    std::string getName() const { return name; }
    void print() override { std::cout << "call virtual void Panda::print()\n"; }
    void toes() override { std::cout << "call virtual void Panda::toes()\n"; }
    void hightlight() override { std::cout << "call virtual void Panda::hightlight()\n"; }
    void cuddle() { std::cout << "call  void Panda::cuddle()\n"; }

private:
    std::string name;
};

void print(const Bear &b) { std::cout << "call void print(const Bear &b), b.name = " << b.getName() << std::endl; }

void hightlight(const Endangered &e)
{
    std::cout << "call void hightlight(const Endangered &e), e.endangered = "
              << std::boolalpha << e.isDangered() << std::noboolalpha
              << (e.isDangered() ? " Endangered\n" : " not Endangered\n");
};

std::ostream &operator<<(std::ostream &os, const ZooAnimal &z)
{
    os << "call std::ostream &operator<<(std::ostream &os, const ZooAnimal &z), z.name = " << z.getName() << std::endl;
    return os;
}

int main(int argc, char const *argv[])
{
    Panda ying_yang("ying_yang", "blackbear", "skyNO.1");
    print(ying_yang);
    hightlight(ying_yang);
    std::cout << ying_yang;
    std::cout << "==========================================================\n";

    Panda yingying("yingying");
    Bear *pb = &yingying;
    pb->print();
    pb->toes();
    //pb->highlight(); // "Bear"没有成员"highlight"
    //pb->cuddle();    // "Bear"没有成员"cuddle"
    std::cout << "==========================================================\n";

    Endangered *pe = &yingying;
    pe->print();
    //pe->toes(); // "Endangered"没有成员"toes"
    pe->hightlight();
    //pe->cuddle(); // "Endangered"没有成员"cuddle"
    std::cout << "==========================================================\n";

    ZooAnimal *pz = &yingying;
    pz->print();
    //pz->toes();       // "ZooAnimal"没有成员"toes"
    //pz->hightlight(); // "ZooAnimal"没有成员"hightlight"
    //pz->cuddle();     // "ZooAnimal"没有成员"cuddle"

    return 0;
}
