/**
 * @cite Factory Pattern states that when wholesale object initialization becomes too convoluted (due to various reasons like Non-descriptive constructors, or optional parameter hell, etc.) then the object creation can be off-loaded to a factory.
 * Aims at making the API more Descriptive and Coherent.
 *
 * @brief Factory Pattern can be exemplified by a 2D-Point class that can be initialized by both cartesian and polar coordinates.
 * What happens if the type of arguments required for both initialization is the same ?
 * Even if point type is specified, How to identify which argument corresponds to what?
 * What happens when the initialization uses resources that shouldn't be handled in the Point class as it would break the Single Responsibilty Principle?
 * Even if the intialization is handled in a seperate module, How to let the user know of the same?
 */

#include <cmath>
#include <iostream>

/**
 * @brief Point class that represents a 2D-Point having x, y coordinates.
 * Initialized by only cartesian coords and not polar coords.
 * !@warning No Constructor for Polar coordinates
 */
class Point
{
    float x, y;

public:
    /**
     * @brief Construct a new Point object with x & y coordinates.
     *
     * @param x x coordinate
     * @param y y coordinate
     */
    Point(float x, float y) : x(x), y(y) {}

    /**
     * @brief Construct a new Point object
     * !@warning Not allowed as the Constructor signature is the same.
     * @param rho
     * @param theta
     */
    // Point(float rho, float theta): x(rho * std::cos(theta)), y(rho * std::sin(theta)) {}

    friend std::ostream &operator<<(std::ostream &os, Point &p)
    {
        return os << "x : " << p.x << " y : " << p.y << "\n";
    }
};

enum PointType
{
    cartesian,
    polar,
};

/**
 * @brief Point class that represents a 2D-Point having x, y coordinates.
 * Initialized by specifying the type of point.
 * !@warning Constructor is non-descriptive.
 */
class PointByType
{
    float x, y;

public:
    /**
     * @brief Construct a new Point object
     * !@warning Constructor becomes highly non-descriptive.
     * @param a either x or rho
     * @param b either y or theta
     * @param type
     */
    PointByType(float a, float b, PointType type = cartesian)
    {
        if (type == PointType::cartesian)
        {
            x = a, y = b;
        }
        else
        {
            x = a * std::cos(b);
            y = a * std::sin(b);
        }
    }

    friend std::ostream &operator<<(std::ostream &os, PointByType &p)
    {
        return os << "x : " << p.x << " y : " << p.y << "\n";
    }
};

/**
 * @brief Point class that represents a 2D-Point having x, y coordinates.
 * Initialized by the static factory methods.
 * !@warning Breaks Single Responsibility if the initialization requires resource handling.
 */
class PointByFactoryMethod
{
    float x, y;
    /**
     * @brief Constructor is made private to ensure that the object only created using the interna factory methods.
     */
    PointByFactoryMethod(float x, float y) : x(x), y(y) {}

public:
    /**
     * @brief Constructs a new Point with Cartesain Coordinates.
     */
    static PointByFactoryMethod Cartesian(float x, float y)
    {
        return {x, y};
    }

    /**
     * @brief Constructs a new Point with Polar Coordinates.
     */
    static PointByFactoryMethod Polar(float rho, float theta)
    {
        return {rho * std::cos(theta), rho * std::sin(theta)};
    }

    friend std::ostream &operator<<(std::ostream &os, PointByFactoryMethod &p)
    {
        return os << "x : " << p.x << " y : " << p.y << "\n";
    }
};

/**
 * @brief Provides only an API to construct the Point object.
 * As it is a seperate module any resource handling can be done here to avoid breaking the Single Responsisbilty Principle.
 *
 * !@warning There is no clear connection between Point and PointFactory.
 */
class PointFactoryClass
{
    // Constructor is private to avoid object creation of the factory class.
    PointFactoryClass() {}

public:
    /**
     * @brief Constructs a new Point with Cartesain Coordinates.
     */
    static Point Cartesian(float x, float y)
    {
        return {x, y};
    }

    /**
     * @brief Constructs a new Point with Polar Coordinates.
     */
    static Point Polar(float rho, float theta)
    {
        return {rho * std::cos(theta), rho * std::sin(theta)};
    }
};

/**
 * @brief Uses Singleton Pattern to create a singleton Factory object in the class to allow creation of points.
 * Point and Factory are directly linked as the Factory is the inner class of Point.
 */
class PointByInnerFactory
{
    float x, y;
    PointByInnerFactory(float x, float y) : x(x), y(y) {}
    class InnerFactory;

public:
    static InnerFactory Factory;

    friend std::ostream &operator<<(std::ostream &os, PointByInnerFactory &p)
    {
        return os << "x : " << p.x << " y : " << p.y << "\n";
    }
};

/**
 * @brief Definition of the inner factory class that creates the PointByInnerFactory object.
 */
class PointByInnerFactory::InnerFactory
{
public:
    /**
     * @brief Constructs a new Point with Cartesain Coordinates.
     */
    static PointByInnerFactory Cartesian(float x, float y)
    {
        return {x, y};
    }
    /**
     * @brief Constructs a new Point with Polar Coordinates.
     */
    static PointByInnerFactory Polar(float rho, float theta)
    {
        return {rho * std::cos(theta), rho * std::sin(theta)};
    }
};

int main()
{
    auto cart_point = Point(10, 2);
    // ! No polar initialization for Point class.
    // Point polar_point = Point(10, 2);

    std::cout << "Point \n"
              << cart_point;

    // Both Polar and cartesian point can be constructed.
    // ! But the constructor is non-descriptive
    auto cart_PointByType = PointByType(10, 2);
    auto polar_PointByType = PointByType(10, .5, PointType::polar);

    std::cout << "\nPoints By Type \n"
              << cart_PointByType << polar_PointByType;

    // Both Polar and Caretesian points can be constructed with a descriptive API.
    // ! Could break the SRP.
    auto cart_PointByFactoryMethod = PointByFactoryMethod::Cartesian(10, 2);
    auto polar_PointByFactoryMethod = PointByFactoryMethod::Polar(10, .5);

    std::cout << "\nPoints By Factory Method \n"
              << cart_PointByFactoryMethod << polar_PointByFactoryMethod;

    // ! No connection of Point with the Factory Class
    auto cart_PointByFactoryClass = PointFactoryClass::Cartesian(10, 2);
    auto polar_PointByFactoryClass = PointFactoryClass::Polar(10, .5);

    std::cout << "\nPoints By Factory Class \n"
              << cart_PointByFactoryClass << polar_PointByFactoryClass;

    // *Provides direct API through a singleton object in the class.
    auto cart_PointByInnerFactory = PointByInnerFactory::Factory.Cartesian(10, 2);
    auto polar_PointByInnerFactory = PointByInnerFactory::Factory.Polar(10, .5);

    std::cout << "\nPoints By Inner Factory Class \n"
              << cart_PointByInnerFactory << polar_PointByInnerFactory;
    return 0;
}