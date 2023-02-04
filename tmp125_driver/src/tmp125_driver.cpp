#include <iostream>
#include "tmp125_driver.hpp"
#include "gpio_lib.hpp"

namespace tmp125{

int32_t Tmp125Driver::tmp125_init(void)
{
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

int32_t Tmp125Driver::tmp125_read_temp(uint8_t temp_sensor_id, float *p_temp_in_degrees_c)
{
    if (!initialized)
    {
        std::cerr << "Error: Please initialize the tmp125 driver" << std::endl;
        return 2;
    }

    if (temp_sensor_id > 4 or temp_sensor_id < 1)
    {
        std::cerr << "Error: Invalid sensor ID: " << (unsigned int) temp_sensor_id << std::endl;
        return 1;
    }

    /* SPI READ */
    // Force clock to start at HIGH
    // Put CS low for sensor we want to read from to start the read
    gpio_write_pin(constants::TMP125_PORT, constants::SCK_PIN, LOGICAL_HIGH);
    gpio_write_pin(constants::TMP125_PORT, temp_sensor_id + 3, LOGICAL_LOW);

    std::vector<uint8_t> data_word;
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

        // Process/save the bit
        data_word.push_back(pin_bit);

        // Potentially sleep for X ns
    } 

    if (data_word.size() != constants::DATA_WORD_SIZE_BITS)
    {
        std::cerr << "Error: Data word received invalid" << std::endl;
        return 3;
    }
    
    // convert the bits in the data word to the temperature
    *p_temp_in_degrees_c = data_word_to_temp(data_word);

    return 0;
}

float Tmp125Driver::data_word_to_temp(std::vector<uint8_t>& data_word)
{
    /*
        My interpretation of the data word
        Order: [0, (SIGN_BIT, MSB,...LSB), 0, 0, 0, 0, 0] 16 bits
        - Ignore leading / trailing zeros
        Calculating temp value:
        - First bit is signs two's complement
        - Next 7 bits are typical int conversion.
        - Last 2 bits specify 0.25 decimal resolution.. It's not completely clear in the 
          documentation but I believe it's as follows: 00 == .00, 01 = 0.25, 10 = 0.50, 11 = 0.75
        - So according to the examples I would
            1. Perform two's complement on the entire 10 bits if it's negative
            2. Figure out the Int
            3. Figure out the decimal portion
            4. Add them together in a float
            5. Make negative if Two's complement had to be performed

    */
   
   // Holds the int portion of the data word
   uint32_t data_word_int = 0;

    // Holds the float portion of the data word
   float data_word_float = 0;

   // Lets us know at the end if we need to make the calculated value negative
   bool is_negative = false;

   // Remove trailing zeros
   data_word.erase(data_word.begin());
   data_word.pop_back();
   data_word.pop_back();
   data_word.pop_back();
   data_word.pop_back();
   data_word.pop_back();


    // Check if the word is a negative value. If so, two's complement
   if (data_word[0] == 1)
    {
        is_negative = true;
       
        // Perform bitwise NOT
        for (uint64_t i = 0; i < data_word.size(); i++)
        {
            data_word[i] = (data_word[i] ? 0 : 1);
        }

        // Add 1
        for (int i = data_word.size() -1; i >= 0; i--)
        {
            if (data_word[i] == 1)
            {
                data_word[i] = 0;
            } else
            {
                data_word[i] = 1;
                break;
            }
        }
    }

    // Calculate int
    for (int i = 0; i < 8; i++)
    {
        data_word_int |= (data_word[i] << ((constants::DATA_WORD_INT_SIZE_BITS - 1) - i));
    }

    // Calculate float
    if (data_word[8] == 0 and data_word[9] == 0)
    {
        data_word_float = 0;
    } else if (data_word[8] == 0 and data_word[9] == 1)
    {
        data_word_float = 0.25;
    } else if (data_word[8] == 1 and data_word[9] == 0)
    {
        data_word_float = 0.50;
    } else
    {
        data_word_float = 0.75;
    }

    // Add together
    float temperature_deg_c = data_word_float + data_word_int;

    if (is_negative)
    {
        temperature_deg_c *= -1;
    }

    return temperature_deg_c;
}

} // namespace tmp_125