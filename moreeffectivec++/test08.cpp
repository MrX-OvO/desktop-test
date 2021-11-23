#include <iostream>
#include <typeinfo> // typeid

namespace version_1
{
    class GameObject
    {
    public:
        GameObject(double speed = 0.0) : gameObjectSpeed(speed) {}
        virtual void collide(GameObject &otherObject) = 0;
        virtual ~GameObject() = default;

    protected:
        double gameObjectSpeed;
    };

    class CollisionWithUnknownObject
    {
    public:
        CollisionWithUnknownObject(GameObject &otherObject) : otherObj(otherObject) {}
        ~CollisionWithUnknownObject() = default;

    private:
        GameObject &otherObj;
    };

    class SpaceShip : public GameObject
    {
    public:
        SpaceShip(double spaceShipSpeed = 0.0) : GameObject(spaceShipSpeed) {}
        void collide(GameObject &otherObject) override;
        ~SpaceShip() = default;
    };

    class SpaceStation : public GameObject
    {
    public:
        SpaceStation(double spaceStationSpeed = 0.0) : GameObject(spaceStationSpeed) {}
        void collide(GameObject &otherObject) override;
        ~SpaceStation() = default;
    };

    class Asteroid : public GameObject
    {
    public:
        Asteroid(double asreroidSpeed = 0.0) : GameObject(asreroidSpeed) {}
        void collide(GameObject &otherObject) override;
        ~Asteroid() = default;
    };

    void SpaceShip::collide(GameObject &otherObject)
    {
        const std::type_info &objectType = typeid(otherObject);
        if (objectType == typeid(SpaceShip))
        {
            SpaceShip &ss = static_cast<SpaceShip &>(otherObject);
            std::cout << "SpaceShip collide SpaceShip...\n";
        }
        else if (objectType == typeid(SpaceStation))
        {
            SpaceStation &ss = static_cast<SpaceStation &>(otherObject);
            std::cout << "SpaceShip collide SpaceStation...\n";
        }
        else if (objectType == typeid(Asteroid))
        {
            Asteroid &a = static_cast<Asteroid &>(otherObject);
            std::cout << "SpaceShip collide Asteroid...\n";
        }
        else
            throw CollisionWithUnknownObject(otherObject);
    }

    void SpaceStation::collide(GameObject &otherObject)
    {
        const std::type_info &objectType = typeid(otherObject);
        if (objectType == typeid(SpaceShip))
        {
            SpaceShip &ss = static_cast<SpaceShip &>(otherObject);
            std::cout << "SpaceStation collide SpaceShip...\n";
        }
        else if (objectType == typeid(SpaceStation))
        {
            SpaceStation &ss = static_cast<SpaceStation &>(otherObject);
            std::cout << "SpaceStation collide SpaceStation...\n";
        }
        else if (objectType == typeid(Asteroid))
        {
            Asteroid &a = static_cast<Asteroid &>(otherObject);
            std::cout << "SpaceStation collide Asteroid...\n";
        }
        else
            throw CollisionWithUnknownObject(otherObject);
    }

    void Asteroid::collide(GameObject &otherObject)
    {
        const std::type_info &objectType = typeid(otherObject);
        if (objectType == typeid(SpaceShip))
        {
            SpaceShip &ss = static_cast<SpaceShip &>(otherObject);
            std::cout << "Asreroid collide SpaceShip...\n";
        }
        else if (objectType == typeid(SpaceStation))
        {
            SpaceStation &ss = static_cast<SpaceStation &>(otherObject);
            std::cout << "Asreroid collide SpaceStation...\n";
        }
        else if (objectType == typeid(Asteroid))
        {
            Asteroid &a = static_cast<Asteroid &>(otherObject);
            std::cout << "Asreroid collide Asreroid...\n";
        }
        else
            throw CollisionWithUnknownObject(otherObject);
    }
}

namespace version_2
{
    class SpaceShip;
    class SpaceStation;
    class Asteroid;
    class GameObject
    {
    public:
        GameObject(double speed = 0.0) : gameObjectSpeed(speed) {}
        virtual void collide(GameObject &otherObject) = 0;
        virtual void collide(SpaceShip &otherObject) = 0;
        virtual void collide(SpaceStation &otherObject) = 0;
        virtual void collide(Asteroid &otherObject) = 0;
        virtual ~GameObject() = default;

    protected:
        double gameObjectSpeed;
    };

    class SpaceShip : public GameObject
    {
    public:
        SpaceShip(double spaceShipSpeed = 0.0) : GameObject(spaceShipSpeed) {}
        void collide(GameObject &otherObject) override { otherObject.collide(*this); }
        void collide(SpaceShip &otherObject) override { std::cout << "SpaceShip collide SpaceShip...\n"; }
        void collide(SpaceStation &otherObject) override { std::cout << "SpaceShip collide SpaceStation...\n"; }
        void collide(Asteroid &otherObject) override { std::cout << "SpaceShip collide Asteroid...\n"; }
        ~SpaceShip() = default;
    };

    class SpaceStation : public GameObject
    {
    public:
        SpaceStation(double spaceStationSpeed = 0.0) : GameObject(spaceStationSpeed) {}
        void collide(GameObject &otherObject) override { otherObject.collide(*this); }
        void collide(SpaceShip &otherObject) override { std::cout << "SpaceStation collide SpaceShip...\n"; }
        void collide(SpaceStation &otherObject) override { std::cout << "SpaceStation collide SpaceStation...\n"; }
        void collide(Asteroid &otherObject) override { std::cout << "SpaceStation collide Asteroid...\n"; }
        ~SpaceStation() = default;
    };

    class Asteroid : public GameObject
    {
    public:
        Asteroid(double asreroidSpeed = 0.0) : GameObject(asreroidSpeed) {}
        void collide(GameObject &otherObject) override { otherObject.collide(*this); }
        void collide(SpaceShip &otherObject) override { std::cout << "Asteroid collide SpaceShip...\n"; }
        void collide(SpaceStation &otherObject) override { std::cout << "Asteroid collide SpaceStation...\n"; }
        void collide(Asteroid &otherObject) override { std::cout << "Asteroid collide Asteroid...\n"; }
        ~Asteroid() = default;
    };
}

#include <map>
#include <string>
#include <memory> // std::shared_ptr

namespace version_3
{
    class GameObject
    {
    public:
        GameObject(double speed = 0.0) : gameObjectSpeed(speed) {}
        virtual void collide(GameObject &otherObject) = 0;
        virtual ~GameObject() = default;

    protected:
        double gameObjectSpeed;
    };

    class CollisionWithUnknownObject
    {
    public:
        CollisionWithUnknownObject(GameObject &otherObject) : otherObj(otherObject) {}
        ~CollisionWithUnknownObject() = default;

    private:
        GameObject &otherObj;
    };

    class SpaceStation;
    class Asteroid;
    class SpaceShip : public GameObject
    {
    public:
        SpaceShip(double spaceShipSpeed = 0.0) : GameObject(spaceShipSpeed) {}
        void collide(GameObject &otherObject) override;
        virtual void hitSpaceShip(GameObject &sapceShip);
        virtual void hitSpaceStation(GameObject &spaceStation);
        virtual void hitAsteroid(GameObject &asteroid);
        ~SpaceShip() = default;

    public:
        static std::string typeName;

    private:
        using HitFunctionPtr = void (SpaceShip::*)(GameObject &);
        using HitMap = std::map<std::string, HitFunctionPtr>;
        static HitFunctionPtr lookup(const GameObject &whatWeHit);
        static HitMap *initCollisionMap();
        static std::string getTypeName(const std::string &objFullType);
    };

    std::string SpaceShip::typeName = "SpaceShip";

    SpaceShip::HitFunctionPtr SpaceShip::lookup(const GameObject &whatWeHit)
    {
        static std::shared_ptr<HitMap> collisionMap(initCollisionMap());
        std::string objFullType = typeid(whatWeHit).name();
        std::string objType = getTypeName(objFullType);
        HitMap::iterator mapEntry = collisionMap->find(objType);
        if (mapEntry == collisionMap->end())
            return nullptr;
        return (*mapEntry).second;
    }

    void SpaceShip::collide(GameObject &otherObject)
    {
        HitFunctionPtr hfp = lookup(otherObject);
        if (hfp)
            (this->*hfp)(otherObject);
        else
            throw CollisionWithUnknownObject(otherObject);
    }

    void SpaceShip::hitSpaceShip(GameObject &sapceShip)
    {
        SpaceShip &otherShip = dynamic_cast<SpaceShip &>(sapceShip);
        std::cout << "SpaceShip hitSpaceShip...\n";
    }

    class Asteroid;
    class SpaceStation : public GameObject
    {
    public:
        SpaceStation(double spaceStationSpeed = 0.0) : GameObject(spaceStationSpeed) {}
        void collide(GameObject &otherObject) override;
        virtual void hitSpaceShip(GameObject &sapceShip);
        virtual void hitSpaceStation(GameObject &spaceStation);
        virtual void hitAsteroid(GameObject &asteroid);
        ~SpaceStation() = default;

    public:
        static std::string typeName;

    private:
        using HitFunctionPtr = void (SpaceStation::*)(GameObject &);
        using HitMap = std::map<std::string, HitFunctionPtr>;
        static HitFunctionPtr lookup(const GameObject &whatWeHit);
        static HitMap *initCollisionMap();
        static std::string getTypeName(const std::string &objFullType);
    };

    void SpaceShip::hitSpaceStation(GameObject &spaceStation)
    {
        SpaceStation &otherStation = dynamic_cast<SpaceStation &>(spaceStation);
        std::cout << "SpaceShip hitSpaceStation...\n";
    }

    std::string SpaceStation::typeName = "SpaceStation";

    SpaceStation::HitFunctionPtr SpaceStation::lookup(const GameObject &whatWeHit)
    {
        static std::shared_ptr<HitMap> collisionMap(initCollisionMap());
        std::string objFullType = typeid(whatWeHit).name();
        std::string objType = getTypeName(objFullType);
        HitMap::iterator mapEntry = collisionMap->find(objType);
        if (mapEntry == collisionMap->end())
            return nullptr;
        return (*mapEntry).second;
    }

    void SpaceStation::collide(GameObject &otherObject)
    {
        HitFunctionPtr hfp = lookup(otherObject);
        if (hfp)
            (this->*hfp)(otherObject);
        else
            throw CollisionWithUnknownObject(otherObject);
    }

    void SpaceStation::hitSpaceShip(GameObject &sapceShip)
    {
        SpaceShip &otherShip = dynamic_cast<SpaceShip &>(sapceShip);
        std::cout << "SpaceStation hitSpaceShip...\n";
    }

    void SpaceStation::hitSpaceStation(GameObject &spaceStation)
    {
        SpaceStation &otherStation = dynamic_cast<SpaceStation &>(spaceStation);
        std::cout << "SpaceStation hitSpaceStation...\n";
    }

    class Asteroid : public GameObject
    {
    public:
        Asteroid(double asteroidSpeed = 0.0) : GameObject(asteroidSpeed) {}
        void collide(GameObject &otherObject) override;
        virtual void hitSpaceShip(GameObject &sapceShip);
        virtual void hitSpaceStation(GameObject &spaceStation);
        virtual void hitAsteroid(GameObject &asteroid);
        ~Asteroid() = default;

    public:
        static std::string typeName;

    private:
        using HitFunctionPtr = void (Asteroid::*)(GameObject &);
        using HitMap = std::map<std::string, HitFunctionPtr>;
        static HitFunctionPtr lookup(const GameObject &whatWeHit);
        static HitMap *initCollisionMap();
        static std::string getTypeName(const std::string &objFullType);
    };

    std::string SpaceShip::getTypeName(const std::string &objFullType)
    {
        std::string objType;
        if (objFullType.find(SpaceShip::typeName) != objFullType.npos)
            objType = SpaceShip::typeName;
        else if (objFullType.find(SpaceStation::typeName) != objFullType.npos)
            objType = SpaceStation::typeName;
        else if (objFullType.find(Asteroid::typeName) != objFullType.npos)
            objType = Asteroid::typeName;
        return objType;
    }

    SpaceShip::HitMap *SpaceShip::initCollisionMap()
    {
        HitMap *phm = new HitMap;
        (*phm)[SpaceShip::typeName] = &version_3::SpaceShip::hitSpaceShip;
        (*phm)[SpaceStation::typeName] = &version_3::SpaceShip::hitSpaceStation;
        (*phm)[Asteroid::typeName] = &version_3::SpaceShip::hitAsteroid;
        return phm;
    }

    void SpaceShip::hitAsteroid(GameObject &asteroid)
    {
        Asteroid &otherAsteroid = dynamic_cast<Asteroid &>(asteroid);
        std::cout << "SpaceShip hitAsteroid...\n";
    }

    std::string SpaceStation::getTypeName(const std::string &objFullType)
    {
        std::string objType;
        if (objFullType.find(SpaceShip::typeName) != objFullType.npos)
            objType = SpaceShip::typeName;
        else if (objFullType.find(SpaceStation::typeName) != objFullType.npos)
            objType = SpaceStation::typeName;
        else if (objFullType.find(Asteroid::typeName) != objFullType.npos)
            objType = Asteroid::typeName;
        return objType;
    }

    SpaceStation::HitMap *SpaceStation::initCollisionMap()
    {
        HitMap *phm = new HitMap;
        (*phm)[SpaceShip::typeName] = &version_3::SpaceStation::hitSpaceShip;
        (*phm)[SpaceStation::typeName] = &version_3::SpaceStation::hitSpaceStation;
        (*phm)[Asteroid::typeName] = &version_3::SpaceStation::hitAsteroid;
        return phm;
    }

    void SpaceStation::hitAsteroid(GameObject &asteroid)
    {
        Asteroid &otherAsteroid = dynamic_cast<Asteroid &>(asteroid);
        std::cout << "SpaceStation hitAsteroid...\n";
    }

    std::string Asteroid::typeName = "Asteroid";

    std::string Asteroid::getTypeName(const std::string &objFullType)
    {
        std::string objType;
        if (objFullType.find(SpaceShip::typeName) != objFullType.npos)
            objType = SpaceShip::typeName;
        else if (objFullType.find(SpaceStation::typeName) != objFullType.npos)
            objType = SpaceStation::typeName;
        else if (objFullType.find(Asteroid::typeName) != objFullType.npos)
            objType = Asteroid::typeName;
        return objType;
    }

    Asteroid::HitMap *Asteroid::initCollisionMap()
    {
        HitMap *phm = new HitMap;
        (*phm)[SpaceShip::typeName] = &version_3::Asteroid::hitSpaceShip;
        (*phm)[SpaceStation::typeName] = &version_3::Asteroid::hitSpaceStation;
        (*phm)[Asteroid::typeName] = &version_3::Asteroid::hitAsteroid;
        return phm;
    }

    Asteroid::HitFunctionPtr Asteroid::lookup(const GameObject &whatWeHit)
    {
        static std::shared_ptr<HitMap> collisionMap(initCollisionMap());
        std::string objFullType = typeid(whatWeHit).name();
        std::string objType = getTypeName(objFullType);
        HitMap::iterator mapEntry = collisionMap->find(objType);
        if (mapEntry == collisionMap->end())
            return nullptr;
        return (*mapEntry).second;
    }

    void Asteroid::collide(GameObject &otherObject)
    {
        HitFunctionPtr hfp = lookup(otherObject);
        if (hfp)
            (this->*hfp)(otherObject);
        else
            throw CollisionWithUnknownObject(otherObject);
    }

    void Asteroid::hitSpaceShip(GameObject &sapceShip)
    {
        SpaceShip &otherShip = dynamic_cast<SpaceShip &>(sapceShip);
        std::cout << "Asteroid hitSpaceShip...\n";
    }

    void Asteroid::hitSpaceStation(GameObject &spaceStation)
    {
        SpaceStation &otherStation = dynamic_cast<SpaceStation &>(spaceStation);
        std::cout << "Asteroid hitSpaceStation...\n";
    }

    void Asteroid::hitAsteroid(GameObject &asteroid)
    {
        Asteroid &otherAsteroid = dynamic_cast<Asteroid &>(asteroid);
        std::cout << "Asteroid hitAsteroid...\n";
    }
}

#include <utility> // std::pair

namespace version_4
{
    class GameObject
    {
    public:
        GameObject(double speed = 0.0) : gameObjectSpeed(speed) {}
        virtual ~GameObject() = default;

    protected:
        double gameObjectSpeed;
    };

    class UnknowCollision
    {
    public:
        UnknowCollision(GameObject &obj1, GameObject &obj2) : object1(obj1), object2(obj2) {}
        ~UnknowCollision() = default;

    private:
        GameObject &object1;
        GameObject &object2;
    };

    class SpaceShip : public GameObject
    {
    public:
        SpaceShip(double spaceShipSpeed = 0.0) : GameObject(spaceShipSpeed) {}
        ~SpaceShip() = default;
    };

    class SpaceStation : public GameObject
    {
    public:
        SpaceStation(double spaceStationSpeed = 0.0) : GameObject(spaceStationSpeed) {}
        ~SpaceStation() = default;
    };

    class Asteroid : public GameObject
    {
    public:
        Asteroid(double asteroidSpeed = 0.0) : GameObject(asteroidSpeed) {}
        ~Asteroid() = default;
    };

    namespace
    {
        void shipAsteriod(GameObject &spaceShip, GameObject &asteroid) { std::cout << "SpaceShip collide Asteroid...\n"; }

        void shipStation(GameObject &spaceShip, GameObject &spaceStion) { std::cout << "SpaceShip collide SpaceStation...\n"; }

        void stationAsteroid(GameObject &spaceStation, GameObject &asteroid) { std::cout << "SpaceStation collide Asteroid...\n"; }

        void asteriodShip(GameObject &asteroid, GameObject &spaceShip) { shipAsteriod(spaceShip, asteroid); }

        void stationShip(GameObject &spaceStation, GameObject &spaceShip) { shipStation(spaceShip, spaceStation); }

        void asteriodStation(GameObject &asteroid, GameObject &spaceStation) { stationAsteroid(spaceStation, asteroid); }

        using HitFunctionPtr = void (*)(GameObject &, GameObject &);
        using HitMap = std::map<std::pair<std::string, std::string>, HitFunctionPtr>;
        using objTypePiar = std::pair<std::string, std::string>;

        objTypePiar makeStringPair(const char *s1, const char *s2) { return std::pair<std::string, std::string>(s1, s2); }

        objTypePiar makeObjTypePair(const std::string &objFullType1, const std::string &objFullType2)
        {
            objTypePiar retObjTypePair;
            if (objFullType1.find("SpaceShip") != objFullType1.npos && objFullType2.find("Asteroid") != objFullType2.npos)
                retObjTypePair = makeStringPair("SpaceShip", "Asteroid");
            else if (objFullType1.find("SpaceShip") != objFullType1.npos && objFullType2.find("SpaceStation") != objFullType2.npos)
                retObjTypePair = makeStringPair("SpaceShip", "SpaceStation");
            else if (objFullType1.find("SpaceStation") != objFullType1.npos && objFullType2.find("Asteroid") != objFullType2.npos)
                retObjTypePair = makeStringPair("SpaceStation", "Asteroid");

            else if (objFullType1.find("Asteroid") != objFullType1.npos && objFullType2.find("SpaceShip") != objFullType2.npos)
                retObjTypePair = makeStringPair("Asteroid", "SpaceShip");
            else if (objFullType1.find("SpaceStation") != objFullType1.npos && objFullType2.find("SpaceShip") != objFullType2.npos)
                retObjTypePair = makeStringPair("SpaceStation", "SpaceShip");
            else if (objFullType1.find("Asteroid") != objFullType1.npos && objFullType2.find("SpaceStation") != objFullType2.npos)
                retObjTypePair = makeStringPair("Asteroid", "SpaceStation");
            return retObjTypePair;
        }

        HitMap *initCollision()
        {
            HitMap *phm = new HitMap;
            (*phm)[makeStringPair("SpaceShip", "Asteroid")] = &shipAsteriod;
            (*phm)[makeStringPair("SpaceShip", "SpaceStation")] = &shipStation;
            (*phm)[makeStringPair("SpaceStation", "Asteroid")] = &stationAsteroid;

            (*phm)[makeStringPair("Asteroid", "SpaceShip")] = &shipAsteriod;
            (*phm)[makeStringPair("SpaceStation", "SpaceShip")] = &shipStation;
            (*phm)[makeStringPair("Asteroid", "SpaceStation")] = &stationAsteroid;
            return phm;
        }

        HitFunctionPtr lookup(const std::string &class1, const std::string class2)
        {
            static std::shared_ptr<HitMap> collisionMap(initCollision());
            HitMap::iterator mapEntry = collisionMap->find(std::make_pair(class1, class2));
            if (mapEntry == collisionMap->end())
                return nullptr;
            return (*mapEntry).second;
        }
    }

    void processCollision(GameObject &object1, GameObject &object2)
    {
        auto objTypePair = makeObjTypePair(typeid(object1).name(), typeid(object2).name());
        HitFunctionPtr hfp = lookup(objTypePair.first, objTypePair.second);
        if (hfp)
            hfp(object1, object2);
        else
            throw UnknowCollision(object1, object2);
    }
}

namespace version_5
{
    class GameObject
    {
    public:
        GameObject(double speed = 0.0) : gameObjectSpeed(speed) {}
        virtual ~GameObject() = default;

    protected:
        double gameObjectSpeed;
    };

    class UnknowCollision
    {
    public:
        UnknowCollision(GameObject &obj1, GameObject &obj2) : object1(obj1), object2(obj2) {}
        ~UnknowCollision() = default;

    private:
        GameObject &object1;
        GameObject &object2;
    };

    class SpaceShip : public GameObject
    {
    public:
        SpaceShip(double spaceShipSpeed = 0.0) : GameObject(spaceShipSpeed) {}
        ~SpaceShip() = default;
    };

    class SpaceStation : public GameObject
    {
    public:
        SpaceStation(double spaceStationSpeed = 0.0) : GameObject(spaceStationSpeed) {}
        ~SpaceStation() = default;
    };

    class Asteroid : public GameObject
    {
    public:
        Asteroid(double asteroidSpeed = 0.0) : GameObject(asteroidSpeed) {}
        ~Asteroid() = default;
    };

    namespace
    {
        void shipAsteriod(GameObject &spaceShip, GameObject &asteroid) { std::cout << "SpaceShip collide Asteroid...\n"; }

        void shipStation(GameObject &spaceShip, GameObject &spaceStion) { std::cout << "SpaceShip collide SpaceStation...\n"; }

        void stationAsteroid(GameObject &spaceStation, GameObject &asteroid) { std::cout << "SpaceStation collide Asteroid...\n"; }

        void asteriodShip(GameObject &asteroid, GameObject &spaceShip) { shipAsteriod(spaceShip, asteroid); }

        void stationShip(GameObject &spaceStation, GameObject &spaceShip) { shipStation(spaceShip, spaceStation); }

        void asteriodStation(GameObject &asteroid, GameObject &spaceStation) { stationAsteroid(spaceStation, asteroid); }
    }

    class CollisionMap
    {
    public:
        using HitFunctionPtr = void (*)(GameObject &, GameObject &);
        void addEntry(const std::string &type1, const std::string &type2, HitFunctionPtr collisionFunction, bool symmetric = true)
        {
            auto objTypePair = makeObjTypePair(type1, type2);
            (*phm)[objTypePair] = collisionFunction;
            if (symmetric)
            {
                auto objTypePair = makeObjTypePair(type2, type1);
                (*phm)[objTypePair] = collisionFunction;
            }
        }

        void removeEntry(const std::string &type1, const std::string &type2) { phm->erase(std::make_pair(type1, type2)); }

        HitFunctionPtr lookup(const std::string &type1, const std::string &type2)
        {
            auto objTypePair = std::make_pair(type1, type2);
            HitMap::iterator mapEntry = phm->find(objTypePair);
            if (mapEntry == phm->end())
                return nullptr;
            return (*mapEntry).second;
        }

        void collide(GameObject &object1, GameObject &object2)
        {
            auto objTypePair = makeObjTypePair(typeid(object1).name(), typeid(object2).name());
            HitFunctionPtr hfp = lookup(objTypePair.first, objTypePair.second);
            if (hfp)
                hfp(object1, object2);
            else
                throw UnknowCollision(object1, object2);
        }

        static CollisionMap &theCollisionMap()
        {
            static CollisionMap collisionMap;
            return collisionMap;
        }

    private:
        CollisionMap() : phm(new HitMap) {}
        CollisionMap(const CollisionMap &);

        using objTypePair = std::pair<std::string, std::string>;
        objTypePair makeObjTypePair(const std::string &objFullType1, const std::string &objFullType2)
        {
            objTypePair retObjTypePair;
            if (objFullType1.find("SpaceShip") != objFullType1.npos && objFullType2.find("Asteroid") != objFullType2.npos)
                retObjTypePair = std::make_pair("SpaceShip", "Asteroid");
            else if (objFullType1.find("SpaceShip") != objFullType1.npos && objFullType2.find("SpaceStation") != objFullType2.npos)
                retObjTypePair = std::make_pair("SpaceShip", "SpaceStation");
            else if (objFullType1.find("SpaceStation") != objFullType1.npos && objFullType2.find("Asteroid") != objFullType2.npos)
                retObjTypePair = std::make_pair("SpaceStation", "Asteroid");

            else if (objFullType1.find("Asteroid") != objFullType1.npos && objFullType2.find("SpaceShip") != objFullType2.npos)
                retObjTypePair = std::make_pair("Asteroid", "SpaceShip");
            else if (objFullType1.find("SpaceStation") != objFullType1.npos && objFullType2.find("SpaceShip") != objFullType2.npos)
                retObjTypePair = std::make_pair("SpaceStation", "SpaceShip");
            else if (objFullType1.find("Asteroid") != objFullType1.npos && objFullType2.find("SpaceStation") != objFullType2.npos)
                retObjTypePair = std::make_pair("Asteroid", "SpaceStation");
            return retObjTypePair;
        }

    private:
        using HitMap = std::map<std::pair<std::string, std::string>, HitFunctionPtr>;
        std::shared_ptr<HitMap> phm;
    };

    class RegisterCollisionFunction
    {
    public:
        RegisterCollisionFunction() = delete;
        RegisterCollisionFunction(const std::string &type1,
                                  const std::string &type2,
                                  CollisionMap::HitFunctionPtr collisionFunction,
                                  bool symmetric = true)
        {
            CollisionMap::theCollisionMap().addEntry(type1, type2, collisionFunction, symmetric);
        }
        RegisterCollisionFunction(const RegisterCollisionFunction &) = delete;
        RegisterCollisionFunction &operator=(const RegisterCollisionFunction &) & = delete;
    };
}

int main(int argc, char const *argv[])
{
    std::cout << "=============== namespace version_1 ===============\n";
    version_1::SpaceShip spaceShip1;
    version_1::SpaceStation spaceStation1;
    version_1::Asteroid asteroid1;
    version_1::GameObject *gameObj1 = &spaceShip1;
    version_1::GameObject *gameObj11 = &spaceStation1;
    gameObj1->collide(spaceShip1);
    gameObj1->collide(spaceStation1);
    gameObj1->collide(asteroid1);
    gameObj1->collide(*gameObj11);
    std::cout << "=============== namespace version_1 ===============\n\n";

    std::cout << "=============== namespace version_2 ===============\n";
    version_2::SpaceShip spaceShip2;
    version_2::SpaceStation spaceStation2;
    version_2::Asteroid asteroid2;
    version_2::GameObject *gameObj2 = &spaceStation2;
    version_2::GameObject *gameObj22 = &asteroid2;
    gameObj2->collide(spaceShip2);
    gameObj2->collide(spaceStation2);
    gameObj2->collide(asteroid2);
    gameObj22->collide(*gameObj2);
    std::cout << "=============== namespace version_2 ===============\n\n";

    std::cout << "=============== namespace version_3 ===============\n";
    version_3::SpaceShip spaceShip3;
    version_3::SpaceStation spaceStation3;
    version_3::Asteroid asteroid3;
    version_3::GameObject *gameObj3 = &asteroid3;
    version_3::GameObject *gameObj33 = &spaceShip3;
    gameObj3->collide(spaceShip3);
    gameObj3->collide(spaceStation3);
    gameObj3->collide(asteroid3);
    gameObj33->collide(*gameObj3);
    std::cout << "=============== namespace version_3 ===============\n\n";

    std::cout << "=============== namespace version_4 ===============\n";
    version_4::SpaceShip spaceShip4;
    version_4::SpaceStation spaceStation4;
    version_4::Asteroid asteroid4;
    version_4::processCollision(spaceShip4, spaceStation4);
    version_4::processCollision(spaceShip4, asteroid4);
    version_4::processCollision(spaceStation4, asteroid4);
    version_4::processCollision(spaceStation4, spaceShip4);
    version_4::processCollision(asteroid4, spaceStation4);
    version_4::processCollision(asteroid4, spaceShip4);
    std::cout << "=============== namespace version_4 ===============\n\n";

    std::cout << "=============== namespace version_5 ===============\n";
    version_5::CollisionMap::theCollisionMap();
    version_5::SpaceShip spaceShip5;
    version_5::SpaceStation spaceStation5;
    version_5::Asteroid asteroid5;

    version_5::RegisterCollisionFunction registerCollisionFunc1(
        typeid(spaceShip5).name(),
        typeid(spaceStation5).name(),
        &version_5::shipStation);
    version_5::CollisionMap::theCollisionMap().collide(spaceShip5, spaceStation5);
    version_5::CollisionMap::theCollisionMap().collide(spaceStation5, spaceShip5);

    version_5::RegisterCollisionFunction registerCollisionFunc2(
        typeid(asteroid5).name(),
        typeid(spaceShip5).name(),
        &version_5::asteriodShip);
    version_5::CollisionMap::theCollisionMap().collide(asteroid5, spaceShip5);
    version_5::CollisionMap::theCollisionMap().collide(spaceShip5, asteroid5);

    version_5::RegisterCollisionFunction registerCollisionFunc3(
        typeid(asteroid5).name(),
        typeid(spaceStation5).name(),
        &version_5::asteriodStation, false);
    version_5::CollisionMap::theCollisionMap().collide(asteroid5, spaceStation5);

    version_5::RegisterCollisionFunction registerCollisionFunc4(
        typeid(spaceStation5).name(),
        typeid(asteroid5).name(),
        &version_5::stationAsteroid);
    version_5::CollisionMap::theCollisionMap().collide(spaceStation5, asteroid5);
    version_5::CollisionMap::theCollisionMap().collide(asteroid5, spaceStation5);
    std::cout << "=============== namespace version_5 ===============\n\n";

    return 0;
}
