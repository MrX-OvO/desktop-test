#include <iostream>
#include <random>
class Vehicle
{
public:
    virtual Vehicle *copy() const = 0;
    virtual double weight() const = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual ~Vehicle() = default;
};

class RoadVehicle : public Vehicle
{
public:
    RoadVehicle() = default;
    RoadVehicle(double, double);
    RoadVehicle(const RoadVehicle &);
    RoadVehicle &operator=(const RoadVehicle &);
    ~RoadVehicle() = default;

    Vehicle *copy() const override;
    double weight() const override;
    void start() override;
    void stop() override;

private:
    double _weight;
    double _speed;
};

RoadVehicle::RoadVehicle(double weight, double speed = 0.0) : _weight(weight), _speed(0.0) {}

RoadVehicle::RoadVehicle(const RoadVehicle &rv) : _weight(rv._weight), _speed(rv._speed) {}

RoadVehicle &RoadVehicle::operator=(const RoadVehicle &rhs)
{
    if (this != &rhs)
    {
        _weight = rhs._weight;
        _speed = rhs._speed;
    }
    return *this;
}

Vehicle *RoadVehicle::copy() const
{
    return new RoadVehicle(*this);
}

double RoadVehicle::weight() const
{
    return _weight;
}

void RoadVehicle::start()
{
    std::cout << "start RoadVehicle...\n";
    static std::default_random_engine e;
    std::uniform_int_distribution<unsigned> d1;
    std::uniform_real_distribution<double> d2;
    _speed = d1(e) * d2(e);
}

void RoadVehicle::stop()
{
    std::cout << "stop RoadVehicle...\n";
    _speed = 0.0;
}

class VehicleSurrogate
{
public:
    VehicleSurrogate();
    VehicleSurrogate(const Vehicle &);
    VehicleSurrogate(const VehicleSurrogate &);
    VehicleSurrogate &operator=(const VehicleSurrogate &);
    ~VehicleSurrogate();

    double weight() const;
    void start();
    void stop();

private:
    Vehicle *pv;
};

VehicleSurrogate::VehicleSurrogate() : pv(nullptr) {}

VehicleSurrogate::VehicleSurrogate(const Vehicle &v) : pv(v.copy()) {}

VehicleSurrogate::VehicleSurrogate(const VehicleSurrogate &v) : pv(v.pv ? v.pv->copy() : nullptr) {}

VehicleSurrogate &VehicleSurrogate::operator=(const VehicleSurrogate &rhs)
{
    if (this != &rhs)
    {
        delete pv;
        pv = rhs.pv ? rhs.pv->copy() : nullptr;
    }
    return *this;
}

VehicleSurrogate::~VehicleSurrogate()
{
    delete pv;
}

double VehicleSurrogate::weight() const
{
    if (pv == nullptr)
        throw "empty VehicleSurrogate.weight()";
    return pv->weight();
}

void VehicleSurrogate::start()
{
    if (pv == nullptr)
        throw "empty VehicleSurrogate.start()";
    pv->start();
}

void VehicleSurrogate::stop()
{
    if (pv == nullptr)
        throw "empty VehicleSurrogate.stop()";
    pv->stop();
}

int main(int argc, char const *argv[])
{
    VehicleSurrogate parking_lot[10];
    RoadVehicle rv;
    unsigned num_vehicle = 0;
    parking_lot[num_vehicle++] = rv;
    parking_lot[0].start();
    parking_lot[0].stop();

    return 0;
}
