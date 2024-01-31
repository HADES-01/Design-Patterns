#include <iostream>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <unordered_set>
using namespace std;

struct Flower
{
    virtual string str() = 0;
};

struct Rose : Flower
{
    string str() override
    {
        return "A rose";
    }
};

// Decorator Class for Flower.
struct ColorFlower
{
    Flower &fl;
    vector<string> colors;
    ColorFlower(Flower &fl, string color) : fl(fl) { add_color(color); }
    ColorFlower(ColorFlower &fl, string color) : fl(fl.fl), colors(fl.colors) { add_color(color); }
    
    string str()
    {
        string ans = fl.str();
        ans += " that is ";
        for (auto color : colors)
        {
            ans += color;
            if (color != *(--colors.end()))
                ans += " and ";
        }
        return ans;
    }

    void add_color(string color)
    {
        if (find(colors.begin(), colors.end(), color) == colors.end())
            colors.push_back(color);
    }
};

struct RedFlower : ColorFlower
{
    RedFlower(Flower &p) : ColorFlower(p, "red") {}
    RedFlower(ColorFlower &p) : ColorFlower(p, "red") {}
    string str() { return ColorFlower::str(); }
};

struct BlueFlower : ColorFlower
{
    BlueFlower(Flower &p) : ColorFlower(p, "blue") {}
    BlueFlower(ColorFlower &p) : ColorFlower(p, "blue") {}
    string str() { return ColorFlower::str(); }
};