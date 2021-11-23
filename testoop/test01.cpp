class Base
{
public:
    void public_member() {}

protected:
    int protected_member;

private:
    int private_member;
};

struct Public_Derived : public Base
{
    void f1() { public_member(); }
    int f2() { return protected_member; }
    // int f3() { return private_member; } // 成员"Base::private_member"(已声明)不可访问
};

struct Protected_Derived : protected Base
{
    void f1() { public_member(); }
    int f2() { return protected_member; }
    // int f3() { return private_member; } // 成员"Base::private_member"(已声明)不可访问
};

struct Private_Derived : private Base
{
    void f1() { public_member(); }
    int f2() { return protected_member; }
    //int f3() { return private_member; } // 成员"Base::private_member"(已声明)不可访问
};

struct Derived_from_Public : public Public_Derived
{
    void use_base1() { public_member(); }
    int use_base2() { return protected_member; }
    // int use_base3() { return private_member; } // 成员"Base::private_member"(已声明)不可访问
};

struct Derived_from_Protected : public Protected_Derived
{
    void use_base1() { public_member(); }
    int use_base2() { return protected_member; }
    // int use_base3() { return private_member; } // 成员"Base::private_member"(已声明)不可访问
};

struct Derived_from_Private : public Private_Derived
{
    // void use_base1() { public_member(); }// 函数"Base::public_member"(已声明)不可访问
    // int use_base2() { return protected_member; }// 成员"Base::protected_member"(已声明)不可访问
    // int use_base3() { return private_member; } // 成员"Base::private_member"(已声明)不可访问
};

int main(int argc, char const *argv[])
{
    Public_Derived d1;
    Protected_Derived d2;
    Private_Derived d3;

    d1.f1();            // 调用"void Public_Derived::f1()"
    d1.f2();            // 调用"void Public_Derived::f2()"
    d1.public_member(); // 调用"void Base::public_member()"
                        // d1.protected_member; // 成员"Base::protected_member"(已声明)不可访问
                        // d1.private_member; // 成员"Base::private_member"(已声明)不可访问

    d2.f1(); // 调用"void Protected_Derived::f1()"
    d2.f2(); // 调用"void Protected_Derived::f2()"
             // d2.public_member(); // 函数"Base::public_member"(已声明)不可访问
             // d2.protected_member; // 成员"Base::protected_member"(已声明)不可访问
             // d2.private_member; // 成员"Base::private_member"(已声明)不可访问

    d3.f1(); // 调用"void Private_Derived::f1()"
    d3.f2(); // 调用"void Private_Derived::f2()"
             // d2.public_member(); // 函数"Base::public_member"(已声明)不可访问
             // d2.protected_member; // 成员"Base::protected_member"(已声明)不可访问
             // d2.private_member; // 成员"Base::private_member"(已声明)不可访问

    Derived_from_Public dp1;
    Derived_from_Protected dp2;
    Derived_from_Private dp3;

    dp1.f1();            // 调用"void Public_Derived::f1()"
    dp1.f2();            // 调用"void Public_Derived::f2()"
    dp1.public_member(); // 调用"void Base::public_member()"
    dp1.use_base1();     // 调用"void Derived_from_Public::use_base1()"
    dp1.use_base2();     // 调用"void Derived_from_Public::use_base2()"

    dp2.f1();        // 调用"void Public_Derived::f1()"
    dp2.f2();        // 调用"void Public_Derived::f2()"
                     // dp2.public_member(); // 函数"Base::public_member"(已声明)不可访问
    dp2.use_base1(); // 调用"void Derived_from_Protected::use_base1()"
    dp2.use_base2(); // 调用"void Derived_from_Protected::use_base2()"

    dp3.f1(); // 调用"void Public_Derived::f1()"
    dp3.f2(); // 调用"void Public_Derived::f2()"
    // dp3.public_member(); // 函数"Base::public_member"(已声明)不可访问

    Base *pb = &d1;
    // pb = &d2; // 不允许对不可访问的基类"Base"进行转换
    // pb = &d3; // 不允许对不可访问的基类"Base"进行转换
    pb = &dp1;
    // pb = &dp2; // 不允许对不可访问的基类"Base"进行转换
    // pb = &dp3; // 不允许对不可访问的基类"Base"进行转换

    return 0;
}
