/**
 * @file spi_interface.cpp
 * @brief Implementation of the SPIInterface class.
 * @author Maxton Ginier
 */
#include <chrono>
#include <thread>
#include <iostream>

#include "spi_interface.hpp"
#include "gpio_lib.hpp"

using namespace SPI;

SPIInterface::SPIInterface(uint8_t clock_polarity, uint32_t clock_period_ns, uint32_t chip_select_delay_ns, uint8_t port_number):
    clock_polarity{clock_polarity}, clock_period_ns{clock_period_ns}, chip_sel_delay_ns{chip_select_delay_ns}, port_number{port_number}
{
}

int32_t SPIInterface::spi_init(void) const
{
    /* 
    NOTE: Unfinished because I understand I need to check the error code for all of the gpio lib functions,
    however I'm deprioritizing it for this challenge to focus instead on other aspects of the implementation. 
    Plus it hopefully will be cleaner code for you all!
    */

    /* Set pin starting states */
    gpio_write_pin(port_number, constants::SI_PIN, LOGICAL_LOW);     // Not used for this coding challenge
    gpio_write_pin(port_number, constants::SO_PIN, LOGICAL_LOW);     // Assuming it doesn't matter what we set this because it's input
    gpio_write_pin(port_number, constants::SCK_PIN, clock_polarity);   // Clock polarity dictates clock start state
    gpio_write_pin(port_number, constants::CS1_PIN, LOGICAL_HIGH);   // Logical HIGH indicates the sensor is not being used 
    gpio_write_pin(port_number, constants::CS2_PIN, LOGICAL_HIGH);   // Logical HIGH indicates the sensor is not being used 
    gpio_write_pin(port_number, constants::CS3_PIN, LOGICAL_HIGH);   // Logical HIGH indicates the sensor is not being used 
    gpio_write_pin(port_number, constants::CS4_PIN, LOGICAL_HIGH);   // Logical HIGH indicates the sensor is not being used 

    /* Set pin directions */
    gpio_set_direction(port_number, constants::SI_PIN, DIR_OUTPUT);    // Slave Input = Master Output
    gpio_set_direction(port_number, constants::SO_PIN, DIR_INPUT);     // Slave Output = Master Input
    gpio_set_direction(port_number, constants::SCK_PIN, DIR_OUTPUT);   // Outputs the clock chirps 
    gpio_set_direction(port_number, constants::CS1_PIN, DIR_OUTPUT);   // Chip Select outputs the select bit value 
    gpio_set_direction(port_number, constants::CS2_PIN, DIR_OUTPUT);   // Chip Select outputs the select bit value 
    gpio_set_direction(port_number, constants::CS3_PIN, DIR_OUTPUT);   // Chip Select outputs the select bit value 
    gpio_set_direction(port_number, constants::CS4_PIN, DIR_OUTPUT);   // Chip Select outputs the select bit value 
    
    initialized = true;

    return 0;
}

int32_t SPIInterface::spi_read_data_bits(uint32_t* data_word, uint32_t data_size, uint8_t chip_sel) const
{
    if (data_size > constants::MAX_DATA_WORD_SIZE_BITS)
    {
        std::cerr << "Error: Data size > " << constants::MAX_DATA_WORD_SIZE_BITS << " bits" << std::endl;
        return 1;
    }

    // Set the Chip Select for the device we want to read
    gpio_write_pin(port_number, chip_sel, LOGICAL_LOW);
    std::this_thread::sleep_for(std::chrono::nanoseconds(chip_sel_delay_ns));

    // Ensure data word is set to 0 before shifting bits onto it
    *data_word = 0x0;

    for (uint32_t i = 0; i < data_size; i++)
    {
        // Trigger clock cycle
        gpio_write_pin(port_number, constants::SCK_PIN, !clock_polarity);
        std::this_thread::sleep_for(std::chrono::nanoseconds(clock_period_ns));
        gpio_write_pin(port_number, constants::SCK_PIN, clock_polarity);

        // Read data from SO
        uint8_t pin_bit;
        gpio_read_pin(port_number, constants::SO_PIN, &pin_bit);

        // Shift bit value on the data word
        *data_word <<= 1;
        *data_word |= pin_bit;
    }

    // Reset the chip select
    gpio_write_pin(port_number, chip_sel, LOGICAL_HIGH);
    
    return 0;
}