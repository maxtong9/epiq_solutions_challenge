#include "../include/platform_temperature_monitor.hpp"
#include <iostream>
using namespace PTM;


/**
 * @brief Main driver for the PTM Solution utilizing Epiq Solution's challenge criteria
 */
int main()
{
    // Initialize the temperature monitor with the acceptable temperature boundaries
    PlatformTemperatureMonitor p(-40.0, 85.0);

    // Register the four temperature sensors
    p.register_temp_sensor(1);
    p.register_temp_sensor(2);
    p.register_temp_sensor(3);
    p.register_temp_sensor(4);

    // Begin monitoring temperatures
    p.runTemperatureMonitor();
}