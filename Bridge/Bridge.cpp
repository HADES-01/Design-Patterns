/**
 * @cite Bridge Pattern states that when an interface contains multiple features that are variable then their implementation has to be decoupled from the interface in order to avoid the 'Cartesian Entity Exlposion'.
 * Aims at promoting Manageability by keeping the codebase small and reasonable.
 *
 * @brief Bridge Pattern can be exemplified by a Monitor class that needs to support both HDMI and VGA signals as input, and also support both HDR and SDR outputs.
 * Implementating Support for all four variation will need 4 sub-classes like (HDMIMonitorHDR, VGAMonitorSDR etc..), which is not mantainable.
 * What happens when we need to add support DVI signal as well, do we need 2 more sub-classes?
 */

#include "DynamicRange.h"
#include "Input.h"

/**
 * @brief Monitor class supports all the inputs and range variations by bridging through abstractions.
 */
class Monitor
{
    // Bridge to the Signal Specification
    Input &signal;
    // Bridge to the DyanamicRange Specification
    DynamicRange &range;

public:
    /**
     * @brief Construct a new Monitor object with the Input ref and DynamicRange ref.
     */
    Monitor(Input &inp, DynamicRange &dr) : signal(inp), range(dr) {}

    // Displays details about the monitor
    void details()
    {
        std::cout << "Displaying video from a ";
        signal.type();
        std::cout << " at a ";
        range.type();
        std::cout << ".\n";
    }
};

/**
 * @brief To Extend Support to DVI just create a new Input type as DVI.
 * Input implementation for DVI signal.
 */
class DVIInput : public Input
{
public:
    void type() override
    {
        std::cout << "DVI signal";
    }
};

int main()
{
    // Creating a Monitor with VGA as Input and HDR as DynamicRange.
    VGAInput vga;
    HDR hdr;
    Monitor HDR_VGA_monitor = Monitor(vga, hdr);
    HDR_VGA_monitor.details();

    // Creating a Monitor with DVI as Input and SDR as Dynamic Range.
    DVIInput dvi;
    SDR sdr;
    Monitor DVI_SDR_monitor = Monitor(dvi, sdr);
    DVI_SDR_monitor.details();

    return 0;
}