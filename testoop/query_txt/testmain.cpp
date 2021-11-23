#include <iostream>
#include <fstream>
#include "TextQuery.h"
#include "QueryResult.h"
#include "Query.h"
#include "Query.cpp"
#include "WordQuery.h"
#include "NotQuery.h"
#include "AndQuery.h"
#include "OrQuery.h"

void runQueries(std::ifstream &infile);

int main(int argc, char const *argv[])
{
    /*     std::string infilePath = "./The Old Man and the Sea.txt";
    std::ifstream infile(infilePath);
    runQueries(infile); */
    Query q = Query("fiery") & Query("bird") | Query("wind");
    std::cout << q << std::endl;

    return 0;
}

/* void runQueries(std::ifstream &infile)
{
    TextQuery tq(infile);
    while (true)
    {
        std::cout << "enter word to look for, or q to quit: ";
        std::string word;
        if (!(std::cin >> word) || "q" == word)
            break;
        print(tq.query(word), std::cout) << std::endl;
    }
} */