#include <string>

namespace version_1
{
    class Animal
    {
    public:
        Animal(const std::string &name = " ") : animalName(name) {}
        Animal(const Animal &animal) : animalName(animal.animalName) {}
        Animal &operator=(const Animal &rhs) &
        {
            if (this != &rhs)
                animalName = rhs.getName();
            return *this;
        }
        ~Animal() = default;

        virtual std::string getName() const { return animalName; }

    protected:
        std::string animalName;
    };

    class Lizard : public Animal
    {
    public:
        Lizard(unsigned footNums, const std::string &name = " ") : lizardFootNums(footNums), Animal(name) {}
        Lizard(const Lizard &lizard) : lizardFootNums(lizard.lizardFootNums), Animal(lizard) {}
        Lizard &operator=(const Lizard &rhs) &
        {
            if (this != &rhs)
            {
                Animal::operator=(rhs);
                lizardFootNums = rhs.getFootNums();
            }
            return *this;
        }
        ~Lizard() = default;

        std::string getName() const override { return Animal::getName(); }

        unsigned getFootNums() const { return lizardFootNums; }

    private:
        unsigned lizardFootNums;
    };

    class Chicken : public Animal
    {
    public:
        Chicken(unsigned footNums, const std::string &name = " ") : chickenFootNums(footNums), Animal(name) {}
        Chicken(const Chicken &chicken) : chickenFootNums(chicken.chickenFootNums), Animal(chicken) {}
        Chicken &operator=(const Chicken &rhs) &
        {
            if (this != &rhs)
            {
                Animal::operator=(rhs);
                chickenFootNums = rhs.getFootNums();
            }
            return *this;
        }
        ~Chicken() = default;

        std::string getName() const override { return Animal::getName(); }

        unsigned getFootNums() const { return chickenFootNums; }

    private:
        unsigned chickenFootNums;
    };
}

namespace version_2
{
    class Animal
    {
    public:
        Animal(const std::string &name = " ") : animalName(name) {}
        Animal(const Animal &animal) : animalName(animal.animalName) {}
        virtual Animal &operator=(const Animal &rhs) &
        {
            if (this != &rhs)
                animalName = rhs.animalName;
            return *this;
        }
        ~Animal() = default;

        virtual std::string getName() const { return animalName; }

    protected:
        std::string animalName;
    };

    class Lizard : public Animal
    {
    public:
        Lizard(unsigned footNums, const std::string &name = " ") : lizardFootNums(footNums), Animal(name) {}
        Lizard(const Lizard &lizard) : lizardFootNums(lizard.lizardFootNums), Animal(lizard) {}
        Lizard &operator=(const Lizard &rhs) &
        {
            if (this != &rhs)
            {
                Animal::operator=(rhs);
                lizardFootNums = rhs.getFootNums();
            }
            return *this;
        }
        Lizard &operator=(const Animal &rhs) & override { return operator=(dynamic_cast<const Lizard &>(rhs)); }
        ~Lizard() = default;

        std::string getName() const override { return Animal::getName(); }

        unsigned getFootNums() const { return lizardFootNums; }

    private:
        unsigned lizardFootNums;
    };

    class Chicken : public Animal
    {
    public:
        Chicken(unsigned footNums, const std::string &name = " ") : chickenFootNums(footNums), Animal(name) {}
        Chicken(const Chicken &chicken) : chickenFootNums(chicken.chickenFootNums), Animal(chicken) {}
        Chicken &operator=(const Chicken &rhs) &
        {
            if (this != &rhs)
            {
                Animal::operator=(rhs);
                chickenFootNums = rhs.getFootNums();
            }
            return *this;
        }
        Chicken &operator=(const Animal &rhs) & override { return operator=(dynamic_cast<const Chicken &>(rhs)); }
        ~Chicken() = default;

        std::string getName() const override { return Animal::getName(); }

        unsigned getFootNums() const { return chickenFootNums; }

    private:
        unsigned chickenFootNums;
    };
}

namespace version_3
{
    class Animal
    {
    public:
        Animal(const std::string &name = " ") : animalName(name) {}
        Animal(const Animal &animal) : animalName(animal.animalName) {}
        ~Animal() = default;

        virtual std::string getName() const { return animalName; }

    protected:
        std::string animalName;

    private:
        Animal &operator=(const Animal &rhs) &;
    };

    class Lizard : public Animal
    {
    public:
        Lizard(unsigned footNums, const std::string &name = " ") : lizardFootNums(footNums), Animal(name) {}
        Lizard(const Lizard &lizard) : lizardFootNums(lizard.lizardFootNums), Animal(lizard) {}
        Lizard &operator=(const Lizard &rhs) &
        {
            if (this != &rhs)
            {
                animalName = rhs.getName();
                lizardFootNums = rhs.getFootNums();
            }
            return *this;
        }
        ~Lizard() = default;

        std::string getName() const override { return Animal::getName(); }

        unsigned getFootNums() const { return lizardFootNums; }

    private:
        unsigned lizardFootNums;
    };

    class Chicken : public Animal
    {
    public:
        Chicken(unsigned footNums, const std::string &name = " ") : chickenFootNums(footNums), Animal(name) {}
        Chicken(const Chicken &chicken) : chickenFootNums(chicken.chickenFootNums), Animal(chicken) {}
        Chicken &operator=(const Chicken &rhs) &
        {
            if (this != &rhs)
            {
                animalName = rhs.getName();
                chickenFootNums = rhs.getFootNums();
            }
            return *this;
        }
        ~Chicken() = default;

        std::string getName() const override { return Animal::getName(); }

        unsigned getFootNums() const { return chickenFootNums; }

    private:
        unsigned chickenFootNums;
    };
}

#include <iostream>

int main(int argc, char const *argv[])
{
    std::cout << "++++++++++++++ namespace version_1 ++++++++++++++\n";
    version_1::Lizard lizard1(4, "lizard1");
    version_1::Lizard lizard2(5, "lizard2");
    version_1::Animal *pAnimal1 = &lizard1;
    version_1::Animal *pAnimal2 = &lizard2;
    std::cout << "lizard1 name: " << pAnimal1->getName() << ", lizard2 name: " << pAnimal2->getName() << std::endl;
    std::cout << "lizard1 footNums: " << lizard1.getFootNums() << ", lizard2 footNums: " << lizard2.getFootNums() << std::endl;

    *pAnimal1 = *pAnimal2;
    std::cout << "*pAnimal1 = *pAnimal2;\n";
    std::cout << "lizard1 name: " << pAnimal1->getName() << ", lizard2 name: " << pAnimal2->getName() << std::endl;
    std::cout << "lizard1 footNums: " << lizard1.getFootNums() << ", lizard2 footNums: " << lizard2.getFootNums() << std::endl;

    lizard1 = lizard2;
    std::cout << "lizard1 = lizard2;\n";
    std::cout << "lizard1 name: " << lizard1.getName() << ", lizard2 name: " << lizard2.getName() << std::endl;
    std::cout << "lizard1 footNums: " << lizard1.getFootNums() << ", lizard2 footNums: " << lizard2.getFootNums() << std::endl;
    std::cout << "++++++++++++++ namespace version_1 ++++++++++++++\n\n";

    std::cout << "++++++++++++++ namespace version_2 ++++++++++++++\n";
    version_2::Chicken chicken1(4, "chicken1");
    version_2::Chicken chicken2(5, "chicken2");
    version_2::Animal *pAnimal21 = &chicken1;
    version_2::Animal *pAnimal22 = &chicken2;
    std::cout << "chicken1 name: " << pAnimal21->getName() << ", chicken2 name: " << pAnimal22->getName() << std::endl;
    std::cout << "chicken1 footNums: " << chicken1.getFootNums() << ", chicken2 footNums: " << chicken2.getFootNums() << std::endl;

    *pAnimal21 = *pAnimal22;
    std::cout << "*pAnimal21 = *pAnimal22;\n";
    std::cout << "chicken1 name: " << pAnimal21->getName() << ", chicken2 name: " << pAnimal22->getName() << std::endl;
    std::cout << "chicken1 footNums: " << chicken1.getFootNums() << ", chicken2 footNums: " << chicken2.getFootNums() << std::endl;
    std::cout << "++++++++++++++ namespace version_2 ++++++++++++++\n\n";

    return 0;
}
