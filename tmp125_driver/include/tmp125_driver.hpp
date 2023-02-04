/**
 * @file tmp125_driver.hpp
 * @brief Definition of the Tmp125Driver class.
 * @author Maxton Ginier
 */
#pragma once
#include <stdint.h>
#include "spi_interface.hpp"
namespace tmp125
{
namespace constants 
{
/**
 * @brief GPIO port number the TMP125 sensor is connected to
 */
constexpr uint8_t TMP125_PORT = 0;

/**
 * @brief TMP125 Clock Polarity
 */
constexpr uint8_t CLOCK_POLARITY = 1;

/**
 * @brief TMP125 Clock Period (ns)
 */
constexpr uint32_t CLOCK_PERIOD_NS = 100;

/**
 * @brief Chip select delay (ns)
 */
constexpr uint32_t CHIP_SELECT_DELAY_NS = 30;

/**
 * @brief Data word constants
 */
constexpr uint32_t DATA_WORD_SIZE_BITS = 16;
constexpr uint32_t DATA_WORD_NUM_TRAILING_ZEROS = 5;
constexpr uint32_t DATA_WORD_SIGN_BIT_LOCATION = 9;
constexpr uint32_t DATA_WORD_FLOAT_MASK = 0x3;
constexpr uint32_t DATA_WORD_NUM_FLOAT_VAL = 2;
constexpr uint32_t PRECEDING_ZEROS_MASK = 0xFFFFFC00;
constexpr float TEMP_DATA_RESOLUTION = 0.25;

/**
 * @brief Min / Max temperature sensor IDs
 */
constexpr uint8_t MIN_SENSOR_ID = 1;
constexpr uint8_t MAX_SENSOR_ID = 4;

/**
 * @brief Offset of the sensor ID to the chip select port it's hooked up to
 * NOTE: This is a short cut / hacky way to map the sensor ID with the GPIO pins. It only works for purposes of this challenge
 */
constexpr uint8_t CS_PIN_ID_OFFSET = 3;

} // namespace constants

/**
 * @brief Software driver for the TMP125 temperature sensor
 */
class Tmp125Driver
{
public:
    /**
     * @brief Initializes the SPI interface for the TMP125 temperature sensor
     */
    Tmp125Driver();

    /**
     * @brief Destructor that deletes the memory for the SPI Interface
     */
    ~Tmp125Driver();

    /**
     * @brief Initializes the GPIO interface specific to the TMP125 sensor
     * @return int32_t indicating status of the init operation (0=success, anything else indicates error code)
     */
    int32_t tmp125_init(void) const;

    /**
     * @brief Read the temperature of the requested temp sensor in degrees C
     * @param p_temp_in_degrees_c a pointer to a float where the temperature will be written
     * @return int32_t indicating status of the init operation (0=success, anything else indicates error code)
     */
    int32_t tmp125_read_temp(uint8_t temp_sensor_id, float* p_temp_in_degrees_c) const;

    /**
     * @brief Converts the data word read from the sensor to the temperature in degrees C
     * @param data_word unsigned 32 bit data word containing the bits read from the sensor
     * @return float of the temperature in degrees C
     */
    float data_word_to_temperature(uint32_t data_word) const;

protected:
    /**
     * @brief Set to true when the object is initialized, false otherwise
     */
    mutable bool initialized = false; 

    /**
     * @brief SPI Interface pointer used to connect to the physical GPIO pins
     */
    const SPI::SPIInterface* spi_interface; 
};
} // namespace tmp_125