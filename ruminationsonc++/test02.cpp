namespace version_1
{
    class Point
    {
    public:
        Point() = default;
        Point(int x, int y) : _x(x), _y(y) {}
        Point(const Point &p) : _x(p._x), _y(p._y) {}
        Point(Point &&p) noexcept : _x(p._x), _y(p._y)
        {
            p._x = 0;
            p._y = 0;
        }
        Point &operator=(const Point &rhs) &
        {
            if (this != &rhs)
            {
                _x = rhs._x;
                _y = rhs._y;
            }
            return *this;
        }
        Point &operator=(Point &&rhs) &noexcept
        {
            if (this != &rhs)
            {
                _x = rhs._x;
                _y = rhs._y;
                rhs._x = 0;
                rhs._y = 0;
            }
            return *this;
        }
        ~Point() = default;

        int x() const { return _x; }
        int y() const { return _y; }
        Point &x(int xv)
        {
            _x = xv;
            return *this;
        }
        Point &y(int yv)
        {
            _y = yv;
            return *this;
        }

    private:
        int _x;
        int _y;
    };

    class UPoint // 引用计数类
    {
        friend class Handle;
        Point p;    // 所绑定对象
        unsigned u; // 引用计数，始终为1

        UPoint() : p(), u(1) {}
        UPoint(int x, int y) : p(x, y), u(1) {}
        UPoint(const Point &p0) : p(p0), u(1) {}
    };

    class Handle
    {
    public:
        Handle() : up(new UPoint) {}
        Handle(int x, int y) : up(new UPoint(x, y)) {}
        Handle(const Point &p) : up(new UPoint(p)) {}
        Handle(const Handle &h) : up(h.up) { ++up->u; }
        Handle(Handle &&h) noexcept : up(h.up)
        {
            ++up->u;
            h.up = nullptr;
        }
        Handle &operator=(const Handle &rhs) &
        {
            ++rhs.up->u;
            if (--up->u == 0)
                delete up;
            up = rhs.up;
            return *this;
        }
        Handle &operator=(Handle &&rhs) &noexcept
        {
            ++rhs.up->u;
            if (--up->u == 0)
                delete up;
            up = rhs.up;
            rhs.up = nullptr;
            return *this;
        }
        ~Handle()
        {
            if (--up->u == 0)
                delete up;
        }

        int x() const { return up->p.x(); }
        int y() const { return up->p.y(); }
        Handle &x(int xv) // 值语义
        {
            makeCopy();
            up->p.x(xv);
            return *this;
        }
        Handle &y(int yv) // 值语义
        {
            makeCopy();
            up->p.y(yv);
            return *this;
        }

    private:
        UPoint *up;

    private:
        void makeCopy()
        {
            if (up->u != 1)
            {
                --up->u;
                up = new UPoint(up->p);
            }
        }
    };
}

namespace version_2
{
    class Point
    {
    public:
        Point() = default;
        Point(int x, int y) : _x(x), _y(y) {}
        Point(const Point &p) : _x(p._x), _y(p._y) {}
        Point(Point &&p) noexcept : _x(p._x), _y(p._y)
        {
            p._x = 0;
            p._y = 0;
        }
        Point &operator=(const Point &rhs) &
        {
            if (this != &rhs)
            {
                _x = rhs._x;
                _y = rhs._y;
            }
            return *this;
        }
        Point &operator=(Point &&rhs) &noexcept
        {
            if (this != &rhs)
            {
                _x = rhs._x;
                _y = rhs._y;
                rhs._x = 0;
                rhs._y = 0;
            }
            return *this;
        }
        ~Point() = default;

        int x() const { return _x; }
        int y() const { return _y; }
        Point &x(int xv)
        {
            _x = xv;
            return *this;
        }
        Point &y(int yv)
        {
            _y = yv;
            return *this;
        }

    private:
        int _x;
        int _y;
    };

    class Handle
    {
    public:
        Handle() : p(new Point), u(new unsigned(1)) {}
        Handle(int x, int y) : p(new Point(x, y)), u(new unsigned(1)) {}
        Handle(const Point &p0) : p(new Point(p0)), u(new unsigned(1)) {}
        Handle(const Handle &h) : p(h.p), u(h.u) { ++*u; }
        Handle(Handle &&h) noexcept : p(h.p), u(h.u)
        {
            ++*u;
            h.p = nullptr;
            h.u = nullptr;
        }
        Handle &operator=(const Handle &rhs) &
        {
            ++*rhs.u;
            if (--*u == 0)
            {
                delete p;
                delete u;
            }
            p = rhs.p;
            u = rhs.u;
            return *this;
        }
        Handle &operator=(Handle &&rhs) &noexcept
        {
            ++*rhs.u;
            if (--*u == 0)
            {
                delete p;
                delete u;
            }
            p = rhs.p;
            u = rhs.u;
            rhs.p = nullptr;
            rhs.u = nullptr;
            return *this;
        }
        ~Handle()
        {
            if (--*u == 0)
            {
                delete p;
                delete u;
            }
        }

        int x() const { return p->x(); }
        int y() const { return p->y(); }
        Handle &x(int xv) // 值语义
        {
            makeCopy();
            p->x(xv);
            return *this;
        }
        Handle &y(int yv) // 值语义
        {
            makeCopy();
            p->y(yv);
            return *this;
        }

    private:
        Point *p;
        unsigned *u;

    private:
        void makeCopy()
        {
            if (*u != 1)
            {
                --*u;
                p = new Point(*p);
            }
        }
    };
}

namespace version_3
{
    class Point
    {
    public:
        Point() = default;
        Point(int x, int y) : _x(x), _y(y) {}
        Point(const Point &p) : _x(p._x), _y(p._y) {}
        Point &operator=(const Point &rhs) &
        {
            if (this != &rhs)
            {
                _x = rhs._x;
                _y = rhs._y;
            }
            return *this;
        }
        ~Point() = default;

        int x() const { return _x; }
        int y() const { return _y; }
        Point &x(int xv)
        {
            _x = xv;
            return *this;
        }
        Point &y(int yv)
        {
            _y = yv;
            return *this;
        }

    private:
        int _x;
        int _y;
    };

    class UseCount
    {
    public:
        UseCount() : useCount(new unsigned(1)) {}
        UseCount(const UseCount &u) : useCount(u.useCount) { ++*useCount; }
        ~UseCount()
        {
            if (--*useCount == 0)
                delete useCount;
        }

        bool isOnly() const { return *useCount == 1; }
        bool makeOnly()
        {
            if (*useCount == 1)
                return false;
            --*useCount;
            useCount = new unsigned(1);
            return true;
        }
        bool reattach(const UseCount &u)
        {
            ++*u.useCount;
            if (--*useCount == 0)
            {
                delete useCount;
                useCount = u.useCount;
                return true;
            }
            useCount = u.useCount;
            return false;
        }

    private:
        unsigned *useCount;

    private:
        UseCount &operator=(const UseCount &rhs) &;
    };

    class Handle
    {
    public:
        Handle() : p(new Point) {}
        Handle(int x, int y) : p(new Point(x, y)) {}
        Handle(const Point &p) : p(new Point(p)) {}
        Handle(const Handle &h) : p(h.p), u(h.u) {}
        Handle &operator=(const Handle &rhs) &
        {
            if (u.reattach(rhs.u))
                delete p;
            p = rhs.p;
            return *this;
        }
        ~Handle()
        {
            if (u.isOnly())
                delete p;
        }

        int x() const { return p->x(); }
        int y() const { return p->y(); }
        Handle &x(int xv) // 值语义
        {
            if (u.makeOnly())
                p = new Point(*p);
            p->x(xv);
            return *this;
        }
        Handle &y(int yv) // 值语义
        {
            if (u.makeOnly())
                p = new Point(*p);
            p->y(yv);
            return *this;
        }

    private:
        Point *p;
        UseCount u;
    };
}

int main(int argc, char const *argv[])
{

    return 0;
}
