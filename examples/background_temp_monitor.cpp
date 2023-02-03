#include <thread>
#include <chrono>
#include <iostream>
#include <sstream>
#include "platform_temperature_monitor.hpp"

using namespace PTM;

/**
 * @brief Example of running the PTM in the background of a main application.
 */
int main()
{
    // Initialize the temperature monitor with the acceptable temperature boundaries
    std::cout << "Main thread: Initialize PTM object" << std::endl;
    PlatformTemperatureMonitor p1(-40.0, 85.0);

    // Register a single temperature sensor
    std::cout << "Main thread: Register sensor ID 1" << std::endl;
    p1.register_temp_sensor(1);

    // Start monitoring in the background
    std::cout << "Main thread: Start monitoring in the background" << std::endl;
    std::thread ptm_thread(&PlatformTemperatureMonitor::runTemperatureMonitor, &p1);

    // Wait 5 seconds 
    std::cout << "Main thread: Sleep for 5 seconds in the main thread" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    // Add a new temperature sensor
    std::cout << "Main thread: Add sensor ID 3" << std::endl;
    p1.register_temp_sensor(3);

    // Wait 5 seconds 
    std::cout << "Main thread: Sleep for 5 seconds in the main thread" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    // Increase the rate at which the temperatures are polled
    std::cout << "Main thread: Increase temperature polling rate to 100 ms" << std::endl;
    p1.set_polling_time_interval(100);

    // Wait 5 seconds 
    std::cout << "Main thread: Sleep for 5 seconds in the main thread" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    // Add in rest of temp sensors
    std::cout << "Main thread: Add in rest of temp sensors (2, 4)" << std::endl;
    p1.register_temp_sensor(2);
    p1.register_temp_sensor(4);

    // Sleep for 5 seconds
    std::cout << "Main thread: Sleep for 5 seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    // Asynchronously read temperatures of various sensors
    // while the PTM is on another thread
    for(int i = 0; i < 100; i++)
    {
        float temp_value;
        uint8_t sensor_id = (i % 4) + 1;

        if (p1.PTM_read_temp(sensor_id, &temp_value) == 0)
        {
            std::stringstream read_results;
            read_results << "Main thread: " << "Sensor: " << (unsigned int)sensor_id << ", temp: " << temp_value << std::endl;
            std::cout << read_results.str();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }

    // Change frequency to 1000 ms
    std::cout << "Main thread: Change rate of polling to every 1000 ms" << std::endl;
    p1.set_polling_time_interval(1000);

    // Wait 10 seconds 
    std::cout << "Main thread: Sleep for 10 seconds in the main thread" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));

    // Unregister sensors 1 and 4
    std::cout << "Main thread: Unregister sensors 1, 4" << std::endl;
    p1.unregister_temp_sensor(1);
    p1.unregister_temp_sensor(4);

    // Sleep for 10 seconds
    std::cout << "Main thread: Sleep for 10 seconds in the main thread" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));

    // Change frequency to 500 ms
    std::cout << "Main thread: Change rate of polling to every 500 ms" << std::endl;
    p1.set_polling_time_interval(500);

    // Wait 10 seconds 
    std::cout << "Main thread: Sleep for 10 seconds in the main thread" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));

    // Unregister sensors 2 and 3
    std::cout << "Main thread: Unregister sensors 2, 3" << std::endl;
    p1.unregister_temp_sensor(2);
    p1.unregister_temp_sensor(3);

    ptm_thread.join();    

    std::cout << "Main thread: PTM aborted due to having no sensors to read from" << std::endl;

    exit(0);
}