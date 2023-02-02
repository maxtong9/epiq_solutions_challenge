
#include <iostream>
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
        for (uint8_t sensor_id : temp_sensor_ids)
        {
            float reported_temperature_deg_c;
            int error_code;

            error_code = tmp125_read_temp(sensor_id, &reported_temperature_deg_c);

            if (error_code != 0)
            {
                // Interpret Error and stop polling
                auto current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                const char* char_str_current_time = ctime(&current_time);
                std::string str_current_time{char_str_current_time};
                str_current_time.pop_back(); // Removes unecessary newline
                
                // Report Error
                std::cerr << str_current_time << " ";
                std::cerr << "Error: ";
                try{
                    std::cerr << tmp125_api::error_code_to_str.at(error_code) << std::endl;
                } catch (std::out_of_range) 
                {
                    std::cerr << "Error encountered while trying to read temperature data. Undefined error code reported. " << std::endl;
                }
                // Assumption here is to stop running the temperature monitor.
                return;
            }

            // Verify temperature is valid and in range
            verify_temp_in_range(sensor_id, reported_temperature_deg_c);
        }

        // Poll at the given time interval
        std::this_thread::sleep_for(std::chrono::milliseconds(polling_time_interval_ms));
    }
}

void PlatformTemperatureMonitor::register_temp_sensor(uint8_t sensor_id)
{
    temp_sensor_ids.push_back(sensor_id); // TODO: Verify id doesn't already exist
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
        auto current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        const char* char_str_current_time = ctime(&current_time);
        std::string str_current_time{char_str_current_time};
        str_current_time.pop_back();
        std::cout << str_current_time << " Sensor: " << int(sensor_id) << " - reported temperature out of range: " << reported_temp_deg_c << " degrees celsius" << std::endl;
        return false;
    }

    return true;
}

} //namespace PTM