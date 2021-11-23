/*
 * @Autor        : MrX-OvO
 * @Date         : 2021-08-02 14:19:24
 * @LastEditTime : 2021-08-02 15:13:54
 * @LastEditors  : MrX-OvO
 * @Description  : description
 * @FilePath     : /test/testboost/test01.cpp
 * Copyright 2021 MrX-OvO, All Rithts Rerserved
 * 
 To: One is never too old to learn...
 */

#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/version.hpp>

using namespace std;
using namespace boost::placeholders;

int fun(int x, int y)
{
    return x + y;
}

int main()
{
    cout << "boost version " << BOOST_VERSION << endl;
    cout << "boost lib version " << BOOST_LIB_VERSION << endl;

    int m = 1;
    int n = 2;
    cout << boost::bind(fun, _1, _2)(m, n) << endl;
    return 0;
}