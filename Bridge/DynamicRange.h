#include <iostream>

// Dynamic Range abstraction that helps in creating a bridge betwen the DynamicRange feature and its different implementation.
class DynamicRange
{
public:
    virtual void type() = 0;
};

// DynamicRange Implementation for HDR signal.
class HDR:public DynamicRange
{
public:
    void type() override {
        std::cout << "High Dynamic Range";
    }
};

// DynamicRange Implementation for SDR signal.
class SDR:public DynamicRange {
    public:
    void type() override {
        std::cout << "Standard Dynamic Range";
    }
};