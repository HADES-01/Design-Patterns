#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct Renderer {
    virtual string how_to_draw() = 0;
};

struct VectorRenderer : Renderer {
    string how_to_draw() override {
        return "lines";
    }
};

struct RasterRenderer : Renderer {
    string how_to_draw() override {
        return "pixels";
    }
};

struct Shape {
    Renderer &renderer;
    virtual string str() = 0;
    Shape(Renderer &rn): renderer(rn) {}
};

struct Square: Shape {
    Square(Renderer &&renderer) : Shape(renderer) {}
    string str() {
        return "Drawing Square as " + renderer.how_to_draw();
    }
};

struct Triangle: Shape {
    Triangle(Renderer &&renderer) : Shape(renderer) {}
    string str() {
        return "Drawing Triangle as " + renderer.how_to_draw();
    }
};