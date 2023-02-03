#pragma once
#include <set>
#include <cstdint>
#include <mutex>

namespace PTM
{
namespace constants
{
    /**
     * @brief Default time between temperature readings for all sensors
     */
    constexpr uint32_t DEFAULT_POLLING_RATE_MS = 500;
}
/**
 * @brief Platform Temperature Monitor class used to monitor temperatures from multiple sensors
 */
class PlatformTemperatureMonitor
{
public:
    /**
     * Create a new Platform Temperature Monitor object
     * @brief Constructor.
     * @param min_temp_deg_c minimum acceptable temperature for the system
     * @param max_temp_deg_c maximum acceptable temperature for the system
     */
    PlatformTemperatureMonitor(float min_temp_deg_c, float max_temp_deg_c);

    /**
     * @brief Register a new temperature sensor to monitor
     * @param sensor_id ID of the sensor to monitor
     * @return true if sensor successfully registerd, false otherwise
     */
    bool register_temp_sensor(uint8_t sensor_id);

    /**
     * @brief Unregister a temperature sensor to monitor
     * @param sensor_id ID of the sensor to deregister
     * @return true if sensor successfully deregisterd, false otherwise
     */
    bool unregister_temp_sensor(uint8_t sensor_id);

    /**
     * @brief Run the temperature monitor (blocking)
     */
    void runTemperatureMonitor();

    /**
     * @brief set the rate at which temperatures are read
     * @param new_polling_time_interval_ms new time at which to poll (milliseconds)
     */
    void set_polling_time_interval(uint32_t new_polling_time_interval_ms);

    /**
     * @brief Read the temperature of the requested temp sensor
     * @param temp_sensor_id the number of the sensor to read (1-4)
     * @param p_temp_in_degrees_c a pointer to a float where the temperature shall be written in degrees celsius
     * @return int32_t indicating status (0=success, anything else indicates an error code
     */
    int32_t PTM_read_temp(uint8_t temp_sensor_id, float* p_temp_in_degrees_c);

    /**
     * @brief Verify the temperature is in range
     * @param sensor_id ID of the sensor that reported the temperature
     * @param reported_temp_deg_c Reported temperature in celcius
     * @return true if temperature is in range, false otherwise 
     */
    bool verify_temp_in_range(uint8_t sensor_id, float reported_temp_deg_c);

protected:
    /**
     * Holds the temperature sensor IDs
     */ 
    std::set<uint8_t> temp_sensor_ids{};

    /**
     * Time between each temperature read on the sensors
     */ 
    uint32_t polling_time_interval_ms = constants::DEFAULT_POLLING_RATE_MS;

    /**
     * Minimum acceptable temperature
     */ 
    float min_temp_deg_c;

    /**
     * Maximum acceptable temperature
     */ 
    float max_temp_deg_c;

    /**
     * Protects modifying the sensor IDs from within the main thread while polling
     */ 
    std::mutex sensor_ids_mtx;

};
} //namespace PTM