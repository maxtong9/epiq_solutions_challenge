/**
 * @file tmp125_driver.cpp
 * @brief Implementation of the Tmp125Driver class
 * @author Maxton Ginier
 */
#include <iostream>
#include "tmp125_driver.hpp"
#include "gpio_lib.hpp"

namespace tmp125{

int32_t Tmp125Driver::tmp125_init(void) const
{
    /* 
    NOTE: Unfinished because I understand I need to check the error code for all of the gpio lib functions,
    however I'm deprioritizing it for this challenge to focus instead on other aspects of the implementation. 
    Plus it hopefully will be cleaner code for you all!
    */

    /* Set pin starting states */
    gpio_write_pin(constants::TMP125_PORT, constants::UNUSED_PIN, LOGICAL_LOW); // Unused
    gpio_write_pin(constants::TMP125_PORT, constants::SI_PIN, LOGICAL_LOW);     // Not used for this coding challenge
    gpio_write_pin(constants::TMP125_PORT, constants::SO_PIN, LOGICAL_LOW);     // Assuming it doesn't matter what we set this because it's input
    gpio_write_pin(constants::TMP125_PORT, constants::SCK_PIN, LOGICAL_HIGH);   // TMP125 Clocks data on the falling edge
    gpio_write_pin(constants::TMP125_PORT, constants::CS1_PIN, LOGICAL_HIGH);   // Logical HIGH indicates the sensor is not being used 
    gpio_write_pin(constants::TMP125_PORT, constants::CS2_PIN, LOGICAL_HIGH);   // Logical HIGH indicates the sensor is not being used 
    gpio_write_pin(constants::TMP125_PORT, constants::CS3_PIN, LOGICAL_HIGH);   // Logical HIGH indicates the sensor is not being used 
    gpio_write_pin(constants::TMP125_PORT, constants::CS4_PIN, LOGICAL_HIGH);   // Logical HIGH indicates the sensor is not being used 

    /* Set pin directions */
    gpio_set_direction(constants::TMP125_PORT, constants::UNUSED_PIN, DIR_INPUT); // Unused, set to input 
    gpio_set_direction(constants::TMP125_PORT, constants::SI_PIN, DIR_OUTPUT);    // Has the ability to shut down the sensor. Not applicable to this challenge
    gpio_set_direction(constants::TMP125_PORT, constants::SO_PIN, DIR_INPUT);     // Receives the temp data as input
    gpio_set_direction(constants::TMP125_PORT, constants::SCK_PIN, DIR_OUTPUT);   // Outputs the clock chirps 
    gpio_set_direction(constants::TMP125_PORT, constants::CS1_PIN, DIR_OUTPUT);   // Chip Select outputs the select bit value 
    gpio_set_direction(constants::TMP125_PORT, constants::CS2_PIN, DIR_OUTPUT);   // Chip Select outputs the select bit value 
    gpio_set_direction(constants::TMP125_PORT, constants::CS3_PIN, DIR_OUTPUT);   // Chip Select outputs the select bit value 
    gpio_set_direction(constants::TMP125_PORT, constants::CS4_PIN, DIR_OUTPUT);   // Chip Select outputs the select bit value 

    initialized = true;
    return 0;
}

int32_t Tmp125Driver::tmp125_read_temp(uint8_t temp_sensor_id, float *p_temp_in_degrees_c) const
{
    if (!initialized)
    {
        std::cerr << "Error: Please initialize the tmp125 driver" << std::endl;
        return 2;
    }

    if (temp_sensor_id > constants::MAX_SENSOR_ID or temp_sensor_id < constants::MIN_SENSOR_ID)
    {
        std::cerr << "Error: Invalid sensor ID: " << (unsigned int) temp_sensor_id << std::endl;
        return 1;
    }

    // SPI Read
    // Force clock to start at HIGH
    gpio_write_pin(constants::TMP125_PORT, constants::SCK_PIN, LOGICAL_HIGH);
    // Put CS low for sensor we want to read from to start the read
    gpio_write_pin(constants::TMP125_PORT, temp_sensor_id + constants::CS_PIN_ID_OFFSET, LOGICAL_LOW);

    uint32_t data_word = 0;
    for (uint32_t i = 0; i < constants::DATA_WORD_SIZE_BITS; i++)
    {
        // Set clock LOW
        gpio_write_pin(constants::TMP125_PORT, constants::SCK_PIN, LOGICAL_LOW);
        
        // Potentially sleep for X ns
        
        // set clock HIGH
        gpio_write_pin(constants::TMP125_PORT, constants::SCK_PIN, LOGICAL_HIGH);

        // Read SO Bit
        uint8_t pin_bit;
        gpio_read_pin(constants::TMP125_PORT, constants::SO_PIN, &pin_bit);

        // Store the bit value
        data_word <<= 1;
        data_word |= pin_bit;

        // Potentially sleep for X ns
    } 

    // Reset the chip select
    gpio_write_pin(constants::TMP125_PORT, temp_sensor_id + constants::CS_PIN_ID_OFFSET, LOGICAL_HIGH);

    // convert the bits in the data word to the temperature
    *p_temp_in_degrees_c = data_word_to_temperature(data_word);

    return 0;
}

float Tmp125Driver::data_word_to_temperature(uint32_t data_word) const
{
    bool is_negative = false;
    
    // Get rid of trailing zeros
    data_word >>= constants::DATA_WORD_NUM_TRAILING_ZEROS;

    // Check sign bit
    if (data_word >> constants::DATA_WORD_SIGN_BIT_LOCATION == 0x1)
    {
        is_negative = true;

        // Two's complement
        data_word |= constants::PRECEDING_ZEROS_MASK; // Makes preceding 0's now 1's
        data_word = ~data_word;
        data_word++;
    }
    
    // Grab fraction by masking the bits
    uint8_t frac_multiplier = data_word & constants::DATA_WORD_FLOAT_MASK;
    
    // Grab integer by shifting away the float portion
    data_word >>= constants::DATA_WORD_NUM_FLOAT_VAL;

    // Calculate the floating point temperature
    float temperature_deg_c = (constants::TEMP_DATA_RESOLUTION * frac_multiplier) + data_word;

    // Return negative if we had to handle the signed bit
    return is_negative ? temperature_deg_c * -1 : temperature_deg_c;
}

} // namespace tmp_125