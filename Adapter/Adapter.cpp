/**
 * @cite Adapter Pattern states that an existing interface can be 'adapted' or transformed to conform to the required interface by creating a wrapper around the given interface.
 * Aims at promoting robustness as the program becomes resilient to the changes in the dependencies e.g. even if the interface that was adpated changes its API in the future, only the adapter class will have to be changed in order to accomodate the API changes.
 *
 * @brief Adpater Pattern can be exemplified by a Graphics interface provided by some library that is used throughout the program.
 * What happens when the interface provided by the library changes in the future?
 */

#include <iostream>
#include <stdexcept>
#include <vector>

/**
 * @brief Graphics interface provided by some library.
 * !@warning Graphics interface changes in the future and deprecates `drawSquare()`.
 */
class Graphics
{
public:
    // ! Provides free access to the internal data.
    int internal_data;

    // Draws a Rectangle
    void drawRectangle()
    {
        std::cout << "Drawing a Rectangle or a square\n";
    }

    /**
     * @brief Draws a Square.
     * !@warning Deprecated as it is redundant. Use `drawRectangle()`.
     */
    void drawSquare()
    {
        throw std::runtime_error("drawSquare() was deprecated.");
    }

    // Draws a Circle
    void drawCircle()
    {
        std::cout << "Drawing a Circle\n";
    }
};

/**
 * @brief The Required Graphics API to be use in the program.
 */
class RequiredGraphicsAPI
{
public:
    virtual void drawRectangle() = 0;
    virtual void drawSquare() = 0;
    virtual void drawCircle() = 0;
};

/**
 * @brief Graphics interface adapted to the RequiredGraphicsAPI.
 */
class GraphicsAdapter : public RequiredGraphicsAPI
{
    // * Hides the internal data and exposes only the required methods.
    Graphics gr;

public:
    // Draws a Rectangle.  Uses `Graphics::drawRectangle()`
    void drawRectangle() override
    {
        gr.drawRectangle();
    }
    /**
     * @brief Draws a Square.
     * After update to Graphics API uses `drawRectanlge()`
     */
    void drawSquare() override
    {
        // ! Deprecated in the latest update to the Graphics API.
        // gr.drawSquare();
        gr.drawRectangle();
    }

    // Draws a Circle. Uses `Graphics::drawCircle()`
    void drawCircle() override
    {
        gr.drawCircle();
    }
};

int main()
{
    try
    {
        Graphics gr;
        gr.drawCircle();
        gr.drawRectangle();
        // ! Results in an error due to latest updates to the API.
        gr.drawSquare();
    }
    catch (std::exception &e)
    {
        std::cout << "ERROR :: " << e.what() << std::endl;
    }

    GraphicsAdapter gr;
    gr.drawCircle();
    gr.drawRectangle();

    // * No Error generated as the Adpater class wa adapted to the changes in the API.
    gr.drawSquare();

    return 0;
}
