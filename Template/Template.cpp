/**
 * @cite Template Pattern states that the skeleton of the algorithm should be defined in the base interface and the details of implementation are decided by the inheritors.
 * Aims at promoting Code Reusability and Modularity.
 *
 * @brief Template Pattern can be exemplified by a Device interface that exposes a single run() function which defines the general flow of device and leaves the implementation details to the inheritors.
 */

#include <iostream>
/**
 * @brief Defines the general flow of a device.
 */
class Device
{
public:
    void run()
    {
        boot();
        load_drivers();
        display();
        get_input();
    }

protected:
    virtual void boot() = 0;
    virtual void load_drivers() = 0;
    virtual void display() = 0;
    virtual void get_input() = 0;
};

/**
 * @brief Implements Device with Android related functionalities.
 */
class AndroidDevice : public Device
{
    void boot() override {
        std::cout << "Booting up the Android Device....\n";
    }

    void load_drivers() override {
        std::cout << "Loading Drivers for Android hardware...\n";
    }

    void display() override {
        std::cout << "Display is turned on ...\n";
    }

    void get_input() override {
        std::cout << "Waiting for input....\n";
    }
};


/**
 * @brief Implements Device with Windows related functionalities.
 */
class WindowsDevice : public Device
{
    void boot() override {
        std::cout << "Booting up the Windows Device....\n";
    }

    void load_drivers() override {
        std::cout << "Loading Drivers for Windows hardware...\n";
    }

    void display() override {
        std::cout << "Display is turned on ...\n";
    }

    void get_input() override {
        std::cout << "Waiting for input....\n";
    }
};

int main() 
{
    AndroidDevice ad;
    ad.run();
    std::cout << "\n";
    WindowsDevice wd;
    wd.run();
    return 0;
}