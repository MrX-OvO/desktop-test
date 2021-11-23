#include <iostream>
#include <vector>
#include "string.h"

void quickSort(std::vector<int> data, int start, int end)
{
    auto i = start, j = end;
    int tmp;
    if (i < j)
    {
        //auto tmp = data[i];
        tmp = data[i];
        while (i != j)
        {
            while (j > i && data[j] > tmp)
                --j;
            // std::swap(data[i], data[j]);
            data[i] = data[j];
            while (i < j && data[i] < tmp)
                ++i;
            // std::swap(data[i], data[j]);
            data[j] = data[i];
        }
        data[i] = tmp;
        quickSort(data, start, i - 1);
        quickSort(data, i + 1, end);
    }
}

void QuickSort(std::vector<int> R, int lo, int hi)
//void QuickSort(int R[], int lo, int hi)
{
    int i = lo, j = hi;
    int temp;
    if (i < j)
    {
        temp = R[i];
        while (i != j)
        {
            while (j > i && R[j] > temp)
                --j;
            R[i] = R[j];
            while (i < j && R[i] < temp)
                ++i;
            R[j] = R[i];
        }
        R[i] = temp;
        QuickSort(R, lo, i - 1);
        QuickSort(R, i + 1, hi);
    }
}

int main(int argc, const char **argv)
{
    for (size_t i = 0; i < argc; i++)
    {
        std::cout << "arg[" << i << "] ";
        for (size_t j = 0; j < strlen(argv[i]); j++)
        {
            std::cout << argv[i][j];
        }
        std::cout << std::endl;
    }

    std::cout << "before sort:\n";
    std::vector<int> data = {1, 15, 6, 7, 9};
    int a[] = {1, 15, 6, 7, 9};
    for (auto var : data)
    {
        std::cout << var << "\t";
    }

    std::cout << "\nafter sort:\n";
    QuickSort(data, 0, 4);
    for (auto var : data)
    {
        std::cout << var << "\t";
    }

    return 0;
}