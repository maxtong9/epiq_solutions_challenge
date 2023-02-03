#include <thread>
#include <chrono>
#include "platform_temperature_monitor.hpp"

using namespace PTM;

/**
 * @brief Example of running the PTM in the background of a main application.
 */
int main()
{
    // Initialize the temperature monitor with the acceptable temperature boundaries
    PlatformTemperatureMonitor p1(-40.0, 85.0);

    // Register a single temperature sensor
    p1.register_temp_sensor(1);

    // Start monitoring in the background
    std::thread ptm_thread(&PlatformTemperatureMonitor::runTemperatureMonitor, &p1);

    // Wait 5 seconds, then add in a new temperature sensor
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    p1.register_temp_sensor(3);

    ptm_thread.join();    
}