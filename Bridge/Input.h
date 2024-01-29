#include <iostream>
#include <string>

// Input Signal Abstraction that helps in bridging the different input signal types with their implementation.
class Input
{
public:
    virtual void type() = 0;
};

// Input implementation for HDMI signal.
class HDMIInput : public Input
{
public:
    void type() override
    {
        std::cout << "HDMI signal";
    }
};

// Input implementation for VGA signal.
class VGAInput : public Input
{
public:
    void type() override
    {
        std::cout << "VGA signal";
    }
};