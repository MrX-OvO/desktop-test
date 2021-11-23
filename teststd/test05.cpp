#include <iostream>
#include <iomanip>
#include <cmath>

int main(int argc, char const *argv[])
{
    std::cout << "std::boolalpha"
              << "\ndefault bool values => true: " << true << ", false: " << false
              << "\nalpha bool values => true: " << std::boolalpha << true << ", false: " << false << std::noboolalpha;

    std::cout << "\n\nstd::oct std::hex std::dec"
              << "\ndefault: " << 20 << " " << 1023
              << "\noctal: " << std::oct << 20 << " " << 103
              << "\nhex: " << std::hex << 20 << " " << 1023
              << "\ndecimal: " << std::dec << 20 << " " << 1023;

    std::cout << "\n\nstd::showbase std::oct std::hex std::dec"
              << std::showbase
              << "\ndefault: " << 20 << " " << 1023
              << "\noctal: " << std::oct << 20 << " " << 1023
              << "\nhex: " << std::hex << 20 << " " << 1023
              << "\ndecimal: " << std::dec << 20 << " " << 1023
              << std::noshowbase;

    std::cout << "\n\nstd::showbase std::uppercase std::oct std::hex std::dec"
              << std::showbase << std::uppercase
              << "\ndefault: " << 20 << " " << 1023
              << "\noctal: " << std::oct << 20 << " " << 1023
              << "\nhex: " << std::hex << 20 << " " << 1023
              << "\ndecimal: " << std::dec << 20 << " " << 1023
              << std::noshowbase << std::nouppercase;

    std::cout << "\n\nstd::setprecision(n)"
              << "\nprecision: " << std::cout.precision() << ", value of sqrt(2): " << sqrt(2.0);
    std::cout.precision(10);
    std::cout << "\nprecision: " << std::cout.precision() << ", value of sqrt(2): " << sqrt(2.0);
    std::cout << std::setprecision(12)
              << "\nprecision: " << std::cout.precision() << ", value of sqrt(2): " << sqrt(2.0);

    std::cout << "\n\nstd::scientific std::fixed std::hexfloat std::defaultfloat"
              << "\ndefault format: " << 100 * sqrt(3.0)
              << "\nscientific: " << std::scientific << 100 * sqrt(3.0)
              << "\nfixed: " << std::fixed << 100 * sqrt(3.0)
              << "\nhexfloat: " << std::hexfloat << 100 * sqrt(3.0)
              << "\nuse default: " << std::defaultfloat << 100 * sqrt(3.0);

    std::cout << "\n\nstd::uppercase std::scientific std::fixed std::hexfloat std::defaultfloat"
              << std::uppercase
              << "\ndefault format: " << 100 * sqrt(3.0)
              << "\nscientific: " << std::scientific << 100 * sqrt(3.0)
              << "\nfixed: " << std::fixed << 100 * sqrt(3.0)
              << "\nhexfloat: " << std::hexfloat << 100 * sqrt(3.0)
              << "\nuse default: " << std::defaultfloat << 100 * sqrt(3.0)
              << std::nouppercase;

    int i = -12;
    double d = sqrt(5.0);
    std::cout << "\n\nstd::setw std::left std::right std::internal std::setfill"
              << "\ni: " << std::setw(12) << i << "next col"
              << "\nd: " << std::setw(12) << d << "next col";
    std::cout << std::left
              << "\ni: " << std::setw(12) << i << "next col"
              << "\nd: " << std::setw(12) << d << "next col"
              << std::right;
    std::cout << std::internal
              << "\ni: " << std::setw(12) << i << "next col"
              << "\nd: " << std::setw(12) << d << "next col";
    std::cout << std::defaultfloat << std::setfill('&')
              << "\ni: " << std::setw(12) << i << "next col"
              << "\nd: " << std::setw(12) << d << "next col"
              << std::setfill(' ')
              << std::endl;

    return 0;
}
