#include "../include/platform_temperature_monitor.hpp"
using namespace PTM;

/**
 * @brief Simple driver for the PTM Solution utilizing Epiq Solution's challenge criteria
 */
int main()
{
    // Initialize the temperature monitor with the acceptable temperature boundaries
    PlatformTemperatureMonitor p1(-40.0, 85.0);

    // Register the four temperature sensors
    p1.register_temp_sensor(1);
    p1.register_temp_sensor(2);
    p1.register_temp_sensor(3);
    p1.register_temp_sensor(4);

    // Begin monitoring temperatures
    p1.runTemperatureMonitor();
}