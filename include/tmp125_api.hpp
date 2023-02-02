#pragma once
#include <iostream>
#include <random>
#include <string>

namespace tmp125_api
{
/**
 * @brief Minimum value for the random distribution
 */
constexpr int MIN_DIST = -42; // tests values slightly out of range
/**
 * @brief Maximum value for the random distribution
 */
constexpr int MAX_DIST = 95; // tests values slightly out of range
/**
 * @brief Total number of error codes utilized by the API
 */
constexpr int NUM_ERROR_CODES = 2;

/**
 * @brief Array that maps error code values (indices) to their string representation
 */
std::array<std::string, NUM_ERROR_CODES> error_code_to_str{"OK", "Invalid sensor ID"};

/**
 * @brief Generate a random temperature value within [MIN_DIST, MAX_DIST]
 * @return a randomly generated temperature as a float
 */
inline float generate_random_temperature_value()
{
    // Setup the random generator
    static std::random_device random_device;
    static std::mt19937 random_engine(random_device());
    static std::uniform_int_distribution<int> temp_distribution(MIN_DIST, MAX_DIST);

    // Return the random number as a float
    return static_cast<float>(temp_distribution(random_engine));
}

/**
 * @brief Read the temperature of the requested temperature sensor_id
 * @param temp_sensor_id the id of the temp sensor to read (1-4)
 * @param p_temp_in_degrees_c a pointer to a float where the temperature will be written
 * @return int32_t indicating status (0=success, any other value indicates an error code)
 */ 
inline int32_t tmp125_read_temp(uint8_t temp_sensor_id, float* p_temp_in_degrees_c)
{
    // Check for valid sensor ID (tmp125 only supports 4)
    if (temp_sensor_id < 1 or temp_sensor_id > 4)
    {
        return 1;
    }
    
    // Simulate reading the temperature sensor
    *p_temp_in_degrees_c = generate_random_temperature_value();

    return 0;
}
} // namespace tmp125_api