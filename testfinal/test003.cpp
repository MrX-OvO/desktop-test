#include <iostream>
#include <string>

class Token
{
public:
    Token() : tok(CHAR), cval(' ') {}
    Token(const Token &t) : tok(t.tok) { copyUnion(t); }
    Token(Token &&t) noexcept : tok(t.tok) { copyUnion(t); }
    Token &operator=(const Token &t) &;
    Token &operator=(Token &&) &noexcept;
    Token &operator=(char) &;
    Token &operator=(int) &;
    Token &operator=(double) &;
    Token &operator=(const std::string &) &;
    ~Token();
    std::string getCurrTok();
    const std::string getCurrTok() const;

private:
    enum
    {
        CHAR,
        INT,
        DOUBLE,
        STRING
    } tok;
    union
    {
        char cval;
        int ival;
        double dval;
        std::string sval;
    };
    void copyUnion(const Token &);
    void copyUnion(Token &&);
};

void Token::copyUnion(const Token &t)
{
    switch (t.tok)
    {
    case Token::CHAR:
        cval = t.cval;
        break;
    case Token::INT:
        ival = t.ival;
        break;
    case Token::DOUBLE:
        ival = t.ival;
        break;
    case Token::STRING:
        new (&sval) std::string(t.sval);
        break;
    }
}

void Token::copyUnion(Token &&t)
{
    switch (t.tok)
    {
    case Token::CHAR:
        cval = t.cval;
        break;
    case Token::INT:
        ival = t.ival;
        break;
    case Token::DOUBLE:
        ival = t.ival;
        break;
    case Token::STRING:
        new (&sval) std::string(t.sval);
        t.sval.~basic_string();
        break;
    }
}

Token &Token::operator=(const Token &t) &
{
    if (this != &t)
    {
        if (tok == STRING && t.tok != STRING)
            sval.~basic_string();
        if (tok == STRING && t.tok == STRING)
            sval = t.sval;
        else
            copyUnion(t);
        tok = t.tok;
    }
    return *this;
}

Token &Token::operator=(Token &&t) &noexcept
{
    if (this != &t)
    {
        if (tok == STRING && t.tok != STRING)
            sval.~basic_string();
        if (tok == STRING && t.tok == STRING)
        {
            sval = t.sval;
            t.sval.~basic_string();
        }
        else
            copyUnion(t);
        tok = t.tok;
    }

    return *this;
}

Token &Token::operator=(char c) &
{
    if (tok == STRING)
        sval.~basic_string();
    cval = c;
    tok = CHAR;
    return *this;
}

Token &Token::operator=(int i) &
{
    if (tok == STRING)
        sval.~basic_string();
    ival = i;
    tok = INT;
    return *this;
}

Token &Token::operator=(double d) &
{
    if (tok == STRING)
        sval.~basic_string();
    dval = d;
    tok = DOUBLE;
    return *this;
}

Token &Token::operator=(const std::string &s) &
{
    if (tok == STRING)
        sval = s;
    else
    {
        new (&sval) std::string(s);
        tok = STRING;
    }
    return *this;
}

Token::~Token()
{
    if (tok == STRING)
        sval.~basic_string();
}

std::string Token::getCurrTok()
{
    std::string ret;
    if (tok == CHAR)
        ret = "CHAR";
    if (tok == INT)
        ret = "INt";
    if (tok == DOUBLE)
        ret = "DOUBLE";
    if (tok == STRING)
        ret = "STRING";
    return ret;
}

const std::string Token::getCurrTok() const
{
    std::string ret;
    if (tok == CHAR)
        ret = "CHAR";
    if (tok == INT)
        ret = "INt";
    if (tok == DOUBLE)
        ret = "DOUBLE";
    if (tok == STRING)
        ret = "STRING";
    return ret;
}

int main(int argc, char const *argv[])
{

    return 0;
}
