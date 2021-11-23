#include "Rational.cpp"
using namespace rational_sp;

int main(int argc, char const *argv[])
{
    std::cout << "=========================================================================================================\n"
              << "Default Constructor or Constructor of Rational...\n";
    Rational r0, r1(1, -1), r2(-1, 2), r3(-2, 3), r4(3, -4), r5(-4, -5), r6(6), r7(7, 0), r8(-2, -8);
    std::cout << "r0 = " << r0 << ", r1  = " << r1 << ", r0 + r1 = " << r0 + r1 << std::endl;
    std::cout << "r2 = " << r2 << ", r3 = " << r3 << ", r2 - r3 = " << r2 - r3 << std::endl;
    std::cout << "r4 = " << r4 << ", r5 = " << r5 << ", r4 * r5 = " << r4 * r5 << std::endl;
    std::cout << "+r4 = " << +r4 << ", -r4 = " << -r4 << std::endl;
    std::cout << "r7 = " << r7 << std::endl;
    std::cout << "r6 = " << r6 << ", r8 = " << r8 << ", r6 / r8 = " << r6 / r8 << std::endl;

    std::cout << "=========================================================================================================\n"
              << "Copy or Move Constructor of Rational...\n";
    Rational cr(r2), mr(std::move(r3));
    std::cout << "cr = " << cr << ", mr = " << mr << ", cr - mr = " << cr - mr << std::endl;

    std::cout << "=========================================================================================================\n"
              << "copy or move asignment of Rational...\n";
    Rational car, mar;
    car = r4, mar = std::move(r5);
    std::cout << "car = " << car << ", mar = " << mar << ", car - mar = " << car - mar << std::endl;

    std::cout << "=========================================================================================================\n"
              << "Initializer_list Constructor or Asignment of Rational...\n";
    Rational r_init_list0{}, r_init_list1({1}), r_init_list2({-2, -3}), r_init_list3;
    r_init_list3 = {-3, 4, 5};
    std::cout << "r_init_list0 = " << r_init_list0 << ", ++r_init_list0 = " << ++r_init_list0 << ", r_init_list0++ = " << r_init_list0++ << std::endl;
    std::cout << "r_init_list1 = " << r_init_list1 << ", --r_init_list1 = " << --r_init_list1 << ", r_init_list1-- = " << r_init_list1-- << std::endl;
    std::cout << "r_init_list0 = " << r_init_list0 << ", r_init_list0 += r_init_list1 " << (r_init_list0 += r_init_list1) << ", r_init_list0 = " << r_init_list0 << std::endl;
    std::cout << "r_init_list1 = " << r_init_list1 << ", r_init_list1 -= r_init_list2 " << (r_init_list1 -= r_init_list2) << ", r_init_list1 = " << r_init_list1 << std::endl;
    std::cout << "r_init_list2 = " << r_init_list2 << ", r_init_list2 *= r_init_list3 " << (r_init_list2 *= r_init_list3) << ", r_init_list2 = " << r_init_list2 << std::endl;
    std::cout << "r_init_list3 = " << r_init_list3 << ", r_init_list3 /= r_init_list3 " << (r_init_list3 /= r_init_list3) << ", r_init_list3 = " << r_init_list3 << std::endl;

    std::cout << "=========================================================================================================\n"
              << "Relationship Operator of Rational...\n";
    std::cout << "r0 = " << r0 << ", r1  = " << r1 << (r0 < r1 ? ", r0 < r1\n" : (r0 == r1 ? ", r0 == r1\n" : ", r0 > r1\n"));
    std::cout << "r2 = " << r2 << ", Rational(1, -2)  = " << Rational(1, -2)
              << (r2 < Rational(1, -2) ? ", r2 < Rational(1, -2)\n" : (r2 == Rational(1, -2) ? ", r2 == Rational(1, -2)\n" : ", r2 > Rational(1, -2)\n"));
    std::cout << "r4 = " << r4 << ", Rational(-3, 4)  = " << Rational(-3, 4)
              << (r4 <= Rational(-3, 4) ? ", r4 <= Rational(-3, 4)\n" : ", r4 > Rational(-3, 4)\n");

    std::cout << "=========================================================================================================\n"
              << "Subscript Operator of Rational...\n";
    std::cout << "r5[0] = " << r5[0] << ", r5[1] = " << r5[1] << ", r5[-1] = " << r5[-1] << ", r5[2] = " << r5[2] << std::endl;
    r5[0] = 1;
    r5[1] = 0;
    std::cout << "r5 = " << r5 << std::endl;
    r5[2] = 5;
    std::cout << "r5 = " << r5 << std::endl;

    std::cout << "=========================================================================================================\n"
              << "Shift Operator of Rational...\n";
    std::cout << "r6 = " << r6 << ", r6 << 2 = " << (r6 << 2) << ", r6 >> 2 = " << (r6 >> 2) << std::endl;
    std::cout << "r6 = " << r6 << ", r6 <<= 2 = " << (r6 <<= 2) << ", r6 >>= 3 = " << (r6 >>= 3) << std::endl;

    std::cout << "=========================================================================================================\n"
              << "Bitwise Operator of Rational...\n";
    Rational r9(5, 4);
    std::cout << "r8 = " << r8 << ", r9 = " << r9 << ", r8 & r9 = " << (r8 & r9) << std::endl;
    std::cout << "r8 = " << r8 << ", r9 = " << r9 << ", r8 | r9 = " << (r8 | r9) << std::endl;
    std::cout << "r8 = " << r8 << ", r9 = " << r9 << ", r8 ^ r9 = " << (r8 ^ r9) << std::endl;
    std::cout << "r8 = " << r8 << ", ~r8 = " << (~r8) << std::endl;

    std::cout << "=========================================================================================================\n"
              << "Logical Operator of Rational...\n";
    std::cout << "r0 = " << r0 << ", !r0 = " << (!r0 ? " ture\n" : " false\n")
              << "r1 = " << r1 << ", !r1 = " << (!r1 ? " ture\n" : " false\n");
    std::cout << "r0 = " << r0 << ", r1 = " << r1 << ", r0 && r1 = " << (r0 && r1 ? " ture\n" : " false\n");
    std::cout << "r1 = " << r1 << ", r2 = " << r2 << ", r1 || r2 = " << (r1 || r2 ? " ture\n" : " false\n");

    std::cout << "=========================================================================================================\n"
              << "Function Call Operator of Rational...\n";
    Rational funcR;
    std::cout << "funcR(1, 2) = " << funcR(1, 2) << std::endl;

    return 0;
}
