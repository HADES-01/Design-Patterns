/**
 * @cite Visitor Pattern states that in order to add new operations to without breaking the OCP and SRP, A visitor structure should be setup beforehand that defines the new operation for all the components in the heirarchy.
 * Aims at fostering Extensibility and Mantainability by performing "double dispatch"
 *
 * @brief Visitor Pattern can be exemplified by CityTourist that tours a City.
 */

#include <iostream>

class Paris;
class Delhi;

class CityVisitor
{
public:
    virtual void visit(Paris &p) = 0;
    virtual void visit(Delhi &d) = 0;
};

class CityTourist : public CityVisitor
{
    void visit(Paris &p) override;
    void visit(Delhi &p) override;
};

class City
{
public:
    virtual void accept(CityVisitor *cv) = 0;
};

class Paris : public City
{
public:
    void accept(CityVisitor *cv) override
    {
        cv->visit(*this);
    }
};

class Delhi : public City
{
public:
    void accept(CityVisitor *cv) override
    {
        cv->visit(*this);
    }
};

void CityTourist::visit(Paris &p)
{
    std::cout << "Touring Paris... \n";
}

void CityTourist::visit(Delhi &d)
{
    std::cout << "Touring Delhi... \n";
}

int main()
{
    Delhi dh;
    Paris ps;

    CityTourist cv;

    dh.accept(&cv);
    ps.accept(&cv);
    return 0;
}