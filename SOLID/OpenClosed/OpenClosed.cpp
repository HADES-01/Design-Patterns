/**
 * @cite Open Closed Principle states that a module should be Open for Extensions but Closed for Modifications.
 * Aims at increasing Stability and Mantainability as once a module is stable and tested, making modifications
 * to it can bring unintended side-effects
 *
 * @brief Open Closed Principle can be exemplified by a Shape class that was created with only quadrilaterals in mind.
 * What happens when we need to add support for non-quadrilateral shapes?
 */

#include <array>
#include <vector>
#include <iostream>

/**
 * @brief Shape class created with only quadrilaterals in mind.
 * ! @warning This class is not open for extensions as it is closely coupled with quadrilaterals.
 * ! @warning This class is not closed for modifications as it is not an abstract class or an interface. So, whenever we need to alter its behavior (i.e. draw), we will need to modify it which can in turn break some other part of code that uses it.
 */
class ShapeQuad
{
    std::array<int, 4> sides;

public:
    void draw()
    {
        for (int i = 0; i < 4; i++)
        {
            std::cout << "Drawing side " << i << std::endl;
        }
    };
};

/**
 * @brief Extending works with Rectangle
 */
class RectangleQuad : public ShapeQuad
{
};
/**
 * @brief Extending works with Sqaure
 */
class SquareQuad : public ShapeQuad
{
};

/**
 * ! @warning Extending fails with Circle as it is not a quadrilateral.
 */
class CircleQuad : public ShapeQuad
{
public:
    CircleQuad()
    {
        throw std::runtime_error("Failed to initialize CircleQuad");
    }
};

/**
 * @brief Shape is a Generic class.
 *
 * Shape class is Open for Extension as it is not coupled with any particular shape and can be extended to any shape that can be drawn.
 * Shape class is Closed for Modifications as it is an abstract class.
 */
class Shape
{
public:
    virtual void draw() = 0;
};

/**
 * @brief Extending works with Rectangle
 */
class Rectangle : public Shape
{
    int length;
    int breadth;

public:
    void draw() override
    {
        std::cout << "Drawing a Rectangle\n";
    }
};
/**
 * @brief Extending works with Sqaure
 */
class Square : public Shape
{
    int side;

public:
    void draw() override
    {
        std::cout << "Drawing a Sqaure\n";
    }
};

/**
 * @brief Extending works with Circle as well
 */
class Circle : public Shape
{
    int r;

public:
    void draw() override
    {
        std::cout << "Drawing a Circle\n";
    }
};

int main()
{
    try
    {
        // ! @warning Initialization fails for circle
        RectangleQuad rec;
        SquareQuad square;
        CircleQuad circle;

        std::vector<ShapeQuad *> shapes = {&rec, &square, &circle};
        for (auto shape : shapes)
            shape->draw();
    }
    catch (std::exception &e)
    {
        std::cout <<"Erorr :: " << e.what() << std::endl;
    }

    Rectangle rec;
    Square square;
    Circle circle;

    std::vector<Shape *> shapes = {&rec, &square, &circle};
    for (auto shape : shapes)
        shape->draw();

    return 0;
}