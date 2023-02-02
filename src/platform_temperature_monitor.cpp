
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include <ctime>
#include <string>
#include "../include/tmp125_api.hpp"
#include "../include/platform_temperature_monitor.hpp"

using namespace tmp125_api;

namespace PTM
{
PlatformTemperatureMonitor::PlatformTemperatureMonitor(float min_temp_deg_c, float max_temp_deg_c)
:min_temp_deg_c{min_temp_deg_c}, max_temp_deg_c{max_temp_deg_c}{}

void PlatformTemperatureMonitor::runTemperatureMonitor()
{
    // Main loop to poll sensor temperatures
    while (true)
    {
        if (temp_sensor_ids.size() == 0)
        {
            std::cout << "Error: No temperature sensors registered." << std::endl;
            return;
        }
        {
            // Protects the iteration from registering / deregistering sensor_ids from another thread
            std::lock_guard<std::mutex> lock(sensor_ids_mtx);

            // Read each temperature sensor 
            for (uint8_t sensor_id : temp_sensor_ids)
            {
                float reported_temperature_deg_c;
                int error_code;

                // Assumption is that the actual driver code of tmp125_read_temp is thread safe (Random Number Gen doesn't need to be)
                error_code = tmp125_read_temp(sensor_id, &reported_temperature_deg_c);

                if (error_code != 0)
                {
                    // Interpret Error and stop polling
                    auto current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                    const char* char_str_current_time = ctime(&current_time);
                    std::string str_current_time{char_str_current_time};
                    str_current_time.pop_back(); // Removes unecessary newline
                    
                    // Report Error
                    std::cerr << str_current_time << " "; // TODO: cout is thread safe but not the << operator. 
                    std::cerr << "Error: ";
                    try{
                        std::cerr << tmp125_api::error_code_to_str.at(error_code) << std::endl;
                    } catch (std::out_of_range) 
                    {
                        std::cerr << "Error encountered while trying to read temperature data. Undefined error code reported. " << std::endl;
                    }
                    // Assumption here is to stop running the temperature monitor if bad error code is encountered.
                    return;
                }

                // Verify temperature is valid and in range
                verify_temp_in_range(sensor_id, reported_temperature_deg_c);
            }
        }

        // Poll at the given time interval
        std::this_thread::sleep_for(std::chrono::milliseconds(polling_time_interval_ms));
    }
}

bool PlatformTemperatureMonitor::register_temp_sensor(uint8_t sensor_id)
{
    std::lock_guard<std::mutex> lock(sensor_ids_mtx);

    // Insert element into set
    return temp_sensor_ids.insert(sensor_id).second; // Note: returns the boolean indicator from the return of insert
}

bool PlatformTemperatureMonitor::unregister_temp_sensor(uint8_t sensor_id)
{
    std::lock_guard<std::mutex> lock(sensor_ids_mtx);

    // Remove element from set
    return temp_sensor_ids.erase(sensor_id); // Note: returns the # of elements deleted (0 = false)
}

void PlatformTemperatureMonitor::set_polling_time_interval(uint32_t new_polling_time_interval_ms)
{
    polling_time_interval_ms = new_polling_time_interval_ms;
}

bool PlatformTemperatureMonitor::verify_temp_in_range(uint8_t sensor_id, float reported_temp_deg_c)
{
    // Check if temperature is out of range of acceptable temperature values
    if (reported_temp_deg_c > max_temp_deg_c or reported_temp_deg_c < min_temp_deg_c)
    {
        // Report the error via standard output
        // Note: Consolidating entire message to SS for thread safety - cout is thread safe, << is not.
        std::stringstream alert_message; 

        // Grab date and time
        auto current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        const char* char_str_current_time = ctime(&current_time);
        std::string str_current_time{char_str_current_time};
        str_current_time.pop_back(); // Removes \n from ctime

        // Print alert message
        alert_message << str_current_time << " Sensor: " << int(sensor_id) << " - reported temperature out of range: " << reported_temp_deg_c << " degrees celsius" << std::endl;
        std::cout << alert_message.str();

        return false;
    }

    return true;
}

int32_t PlatformTemperatureMonitor::PTM_read_temp(uint8_t temp_sensor_id, float* p_temp_in_degrees_c)
{
    return tmp125_read_temp(temp_sensor_id, p_temp_in_degrees_c);
}
} //namespace PTM