/**
 * @cite Prototype Pattern states that rather than building new object from scratch, objects should be able to copy or clone already existing objects and make modifications to them.
 * The cloned object should be a deep copy of the existing object to avoid any memory overwriting.
 * Aims at increasing Flexibility and Mantainability by removing the overhead of creating complex objects from scratch.
 *
 * @brief Prototype Pattern can be exemplified by a 'Car' class having pointers to complex attributes like EngineInfo, etc. which themselves have complex attributes.
 * What happens when a new object, constructed using the default copy contructor, is modified?
 * What happens when the object being copied also has multiple layers?
 */

#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Complex Attribute of a Car object.
 *
 */
class EngineInfo
{
public:
    float cylinder_no, litres, horse_power;
    EngineInfo(
        float cylinders,
        float litres,
        float horsepower) : cylinder_no(cylinders), litres(litres), horse_power(horsepower) {}

    friend std::ostream &operator<<(std::ostream &os, EngineInfo &info)
    {
        return os << info.cylinder_no << " cylinders, " << info.litres << "L " << info.horse_power << "HP";
    }

    // Modified copy constructor in the Complex attribute to make the cloning process recursive.
    EngineInfo(const EngineInfo &engine) : cylinder_no(engine.cylinder_no), litres(engine.litres), horse_power(engine.horse_power) {}
};

/**
 * @brief Car Entity having a complex attribute of EnginInfo.
 */
class Car
{
public:
    EngineInfo *engine;
    std::string company_name, car_model;
    int chassis_no;

    Car(std::string car_model,
        std::string company_name,
        EngineInfo *engine, int chassis_no = 0) : engine(engine), car_model(car_model), company_name(company_name) {}

    friend std::ostream &operator<<(std::ostream &os, Car &car)
    {
        return os << car.company_name << " " << car.car_model << " " << *car.engine << '\n';
    }
};

/**
 * @brief Has a modified copy constructor that creates deep copies
 */
class BetterCar : public Car
{
public:
    // Copy constructor makes a deep copy of the EngineInfo attribute
    BetterCar(const BetterCar &car) : Car(car)
    {
        this->engine = new EngineInfo(*car.engine);
    }

    BetterCar(std::string car_model,
              std::string company_name,
              EngineInfo *engine,
              int chassis_no = 0) : Car(car_model, company_name, engine, chassis_no) {}
};

/**
 * @brief Takes a prototype and produces a new car based on the prototype with a different Chassis No.
 */
class CarFactory
{
public:
    static BetterCar &from_prototype(BetterCar &prototype, int chassis_no)
    {
        BetterCar a(prototype);
        a.chassis_no = chassis_no;
        return a;
    }
};

// Newer models of cars are built using the older models as prototypes.
// And the models created are used as prototypes for the actual production with minor tweaks.
int main()
{
    Car gt1("GT1", "Porsche", new EngineInfo(6, 3.2, 550));
    std::cout << gt1 << "\n";

    // ! Highly redundant as most of the configurations are same.
    Car gt2("GT2", "Porsche", new EngineInfo(6, 3.8, 700));
    std::cout << gt2 << '\n';

    // ! Modifies the the engine config of gt2 as well because gt1 is a shallow copy of gt2.
    {
        Car gt2 = gt1;
        gt1.car_model = "GT2";
        gt1.engine->litres = 3.2;
        gt1.engine->horse_power = 550;
        std::cout << gt2 << gt1 << "\n";
    }

    // * Modifies only the new object as the new object is a deep copy.
    {
        BetterCar gt1("GT1", "Porsche", new EngineInfo(6, 3.2, 550));
        BetterCar gt2{gt1};
        gt1.car_model = "GT2";
        gt1.engine->litres = 3.8;
        gt1.engine->horse_power = 700;
        std::cout << gt2 << gt1 << "\n";

        // ! Making new cars from prototype is still complicated.
        {
            std::vector<BetterCar> cars;
            for (int i = 1; i <= 10; i++)
            {
                BetterCar a(gt2);
                a.chassis_no = i;
                cars.push_back(a);
            }
        }

        // * Making new cars from prototype becomes verbose and simple by using a factory.
        {
            std::vector<BetterCar> cars;
            for (int i = 1; i <= 10; i++)
            {
                cars.push_back(CarFactory::from_prototype(gt2, i));
            }
        }
    }

    return 0;
}