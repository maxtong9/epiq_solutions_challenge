/**
 * @file spi_interface.hpp
 * @brief Definition of the SPIInterface class.
 * @author Maxton Ginier
 */
#pragma once
#include <stdint.h>

namespace SPI
{
namespace constants 
{
/**
 * @brief GPIO port number the TMP125 sensor is connected to
 */
constexpr uint8_t DEFAULT_GPIO_PORT = 0;

/**
 * @brief Default number of devices
 */
constexpr uint32_t DEFAULT_NUM_DEVICES = 1;

/**
 * @brief Default clock period in nano seconds
 */
constexpr uint32_t DEFAULT_CLOCK_PERIOD_NS = 100;

/**
 * @brief Default clock polarity
 */
constexpr uint32_t DEFAULT_CLOCK_POLARITY = 0;

/**
 * @brief Default chip select delay (ns)
 */
constexpr uint32_t DEFAULT_CHIP_SELECT_DELAY_NS = 100;

/**
 * @brief Maximum data word size the SPI Interface can handle at a time in bits
 */
constexpr uint32_t MAX_DATA_WORD_SIZE_BITS = sizeof(uint32_t) * 8;

/**
 * @brief Mappings for the GPIO pins needed for an SPI Interface (NOTE: Would consider implementing these in a config file)
 */
constexpr uint8_t UNUSED     = 0;
constexpr uint8_t SI_PIN     = 1;
constexpr uint8_t SO_PIN     = 2;
constexpr uint8_t SCK_PIN    = 3;
constexpr uint8_t CS1_PIN    = 4;
constexpr uint8_t CS2_PIN    = 5;
constexpr uint8_t CS3_PIN    = 6;
constexpr uint8_t CS4_PIN    = 7;

} // namespace constants

/**
 * @brief Implements a bit-banged SPI interface
 */
class SPIInterface
{
public: 
    /**
     * @brief Default Constructor 
     */
    SPIInterface() = default;
    
    /**
     * @brief Parameterized Constructor
     * @param clock_polarity (0 == Clock set to LOW, 1 == clock set to HIGH)
     * 0 = data shifted out on the rising edge
     * 1 = data shifted out on the falling edge
     * @param clock_period_ns Minimum period of the clock in nano seconds
     * @param chip_select_delay_ns Delay after chip select to when data is ready to be read
     * @param port_number Number of the physical GPIO port the SPI connection is using
     */
    SPIInterface(uint8_t clock_polarity, uint32_t clock_period_ns, uint32_t chip_select_delay_ns, uint8_t port_number);

    /**
     * @brief Initializes the GPIO interface for a simple bit-banged SPI protocol
     * @return int32_t indicating status of the init operation (0=success, anything else indicates error code)
     */
    int32_t spi_init(void) const;

    /**
     * @brief Chirps the clock to read data bit by bit. 
     * @param data_word a pointer to an unsigned int where the data will be written
     * @param data_size size (number of bits) of the data to be read. Cannot be greater than MAX_DATA_WORD_SIZE_BITS6666
     * @param chip_sel chip select pin indicating which device we want to read from
     * @return int32_t indicating status of the init operation (0=success, anything else indicates error code)
     */
    int32_t spi_read_data_bits(uint32_t* data_word, uint32_t data_size, uint8_t chip_sel) const;

protected:
    /**
     * @brief Set to true when the object is initialized, false otherwise
     */
    mutable bool initialized = false; 

    /**
     * @brief Polarity of the clock (0 == low, 1 == high)
     * 0 = data shifted out on the rising edge
     * 1 = data shifted out on the falling edge
     */
    uint8_t clock_polarity = constants::DEFAULT_CLOCK_POLARITY;

    /**
     * @brief Period of the clock in nano seconds
     */
    uint32_t clock_period_ns = constants::DEFAULT_CLOCK_PERIOD_NS;

    /**
     * @brief Waiting period (ns) between triggering the chip select and data available
     */
    uint32_t chip_sel_delay_ns = constants::DEFAULT_CHIP_SELECT_DELAY_NS;

    /**
     * @brief Physical GPIO port the SPI connection is using
     */
    uint32_t port_number = constants::DEFAULT_GPIO_PORT;
};
} // namespace tmp_125