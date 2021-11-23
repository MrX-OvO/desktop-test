#include <iostream>
#include <iomanip>
#include <string>
class Quote
{
    friend double print_total(const Quote &, size_t, std::ostream &);

private:
    std::string bookNo;

protected:
    double sales_price;

public:
    Quote() = default;
    Quote(const std::string &book, double price) : bookNo(book), sales_price(price) {}
    virtual ~Quote() = default;
    std::string isbn() const { return bookNo; }
    virtual double net_price(size_t n) const { return n * sales_price; }
    virtual Quote *clone() const & { return new Quote(*this); }
    virtual Quote *clone() && { return new Quote(std::move(*this)); }
};

double print_total(const Quote &item, size_t n, std::ostream &os = std::cout)
{
    double ret = item.net_price(n);
    os << "ISBN: " << std::setw(2) << item.isbn() << " # sold: " << n << " total due: " << ret << std::endl;
    return ret;
}

class Disc_quote : public Quote
{
protected:
    size_t quantity;
    double discount;

public:
    Disc_quote() = default;
    Disc_quote(const std::string &book, double price, size_t qty, double disc) : Quote(book, price), quantity(qty), discount(disc) {}
    ~Disc_quote() = default;
    double net_price(size_t) const = 0;
};

class Bulk_quote : public Disc_quote
{
private:
    size_t min_qty;
    double discount;

public:
    Bulk_quote() = default;
    Bulk_quote(const std::string &book, double price, size_t qty, double disc) : Disc_quote(book, price, qty, disc), min_qty(qty), discount(disc) {}
    ~Bulk_quote() = default;
    double net_price(size_t) const override;
    virtual Bulk_quote *clone() const & { return new Bulk_quote(*this); }
    virtual Bulk_quote *clone() && { return new Bulk_quote(std::move(*this)); }
};

double Bulk_quote::net_price(size_t cnt) const
{
    if (cnt >= min_qty)
        return cnt * (1 - discount) * sales_price;
    else
        return cnt * sales_price;
}

#include <memory>
#include <set>
class Basket
{
private:
    static bool compare(const std::shared_ptr<Quote> &lhs, const std::shared_ptr<Quote> &rhs) { return lhs->isbn() < rhs->isbn(); }
    std::multiset<std::shared_ptr<Quote>, decltype(compare) *> items{compare};

public:
    void add_item(const std::shared_ptr<Quote> &item) { items.insert(item); }
    void add_item(const Quote &item) { items.insert(std::shared_ptr<Quote>(item.clone())); }
    void add_item(Quote &&item) { items.insert(std::shared_ptr<Quote>(std::move(item).clone())); }
    double total_receipt(std::ostream &) const;
};

double Basket::total_receipt(std::ostream &os = std::cout) const
{
    double sum = 0.0;
    for (auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter))
        sum += print_total(**iter, items.count(*iter), os);
    os << "Total Sale: " << sum << std::endl;
    return sum;
}

#include <cstdlib>
#include <ctime>

int main(int argc, char const *argv[])
{
    Basket bsk;

    srand((unsigned int)NULL);
    for (size_t i = 0; i < 100; ++i)
    {
        std::string book = std::to_string((rand() % 100));
        double price = rand() % 100;
        size_t qty = rand() % 10 + 1;
        double disc = rand() / RAND_MAX;
        Quote q(book, price);
        Bulk_quote b(book, price, qty, disc);
        bsk.add_item(q);
        bsk.add_item(b);
    }
    bsk.total_receipt();

    return 0;
}
