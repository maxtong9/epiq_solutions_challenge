#include <iostream>
#include "tmp125_driver.hpp"
using namespace tmp125;

/**
 * @brief Simple demo for the TMP125 software driver. It reads from all four sensors
 */
int main()
{
    // Create the driver object
    Tmp125Driver driver;
    const uint8_t NUM_SENSORS = 4;

    // Initialize the GPIO pins for TMP125 reading
    driver.tmp125_init();

    // Read the temperature for all four sensors
    for (uint8_t i = 1; i <= NUM_SENSORS; i++)
    {
        float temp_float_deg_c = 0.0;
        driver.tmp125_read_temp(i, &temp_float_deg_c);
        std::cout << "Sensor " << (uint32_t)i << " - temperature: " << temp_float_deg_c << " degrees celsius" << std::endl;
    }
    

    /*
    NOTE:
    If I had more time I would have liked to add more use-cases here.
    But ideally with proper data we would be able to use this in conjunction
    with the PTM Library.

    It's hard to test this class since we don't have actual hardware to test with 
    */
   
}