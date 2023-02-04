/**
 * @file tmp125_driver.cpp
 * @brief Implementation of the Tmp125Driver class
 * @author Maxton Ginier
 */
#include <iostream>
#include "tmp125_driver.hpp"

namespace tmp125{

Tmp125Driver::Tmp125Driver()
{
    spi_interface = new SPI::SPIInterface(constants::CLOCK_POLARITY, constants::CLOCK_PERIOD_NS, constants::CHIP_SELECT_DELAY_NS, constants::TMP125_PORT);
}

Tmp125Driver::~Tmp125Driver() 
{
    delete spi_interface;
}
int32_t Tmp125Driver::tmp125_init(void) const
{
    spi_interface->spi_init();

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

    uint32_t data_word = 0;

    spi_interface->spi_read_data_bits(&data_word, constants::DATA_WORD_SIZE_BITS, temp_sensor_id + constants::CS_PIN_ID_OFFSET);

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