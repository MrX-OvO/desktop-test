#include <iostream>
#include <string>
#include <random>

bool play(bool first) { return first; }

int main(int argc, char const *argv[])
{
    std::string resp;
    std::default_random_engine e;
    std::bernoulli_distribution b(.55);
    do
    {
        bool first = b(e);
        std::cout << (first ? "We go first\n" : "You get to do first\n");
        std::cout << (play(first) ? "Congrats, you won\n" : "Sorry, you lost\n");
        std::cout << "play again? Enter 'yes' or 'no'\n";
    } while (std::cin >> resp && resp[0] == 'y');

    return 0;
}
