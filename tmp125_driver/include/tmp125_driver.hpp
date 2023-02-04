#include <vector>
namespace tmp125{

namespace constants {
// tmp125 Port number
constexpr uint8_t TMP125_PORT = 0;

// Number of bits 
constexpr uint32_t DATA_WORD_SIZE_BITS = 16;
constexpr uint32_t DATA_WORD_INT_SIZE_BITS = 8;
// GPIO Pin mappings
constexpr uint8_t UNUSED_PIN = 0; // Assuming pin 0 is unused according to the diagram given
constexpr uint8_t SI_PIN     = 1;
constexpr uint8_t SO_PIN     = 2;
constexpr uint8_t SCK_PIN    = 3;
constexpr uint8_t CS1_PIN    = 4;
constexpr uint8_t CS2_PIN    = 5;
constexpr uint8_t CS3_PIN    = 6;
constexpr uint8_t CS4_PIN    = 7;
} // namespace constants

class Tmp125Driver
{
public:    
    /* Description: Provide any necessary initialization of the library
    Parameters: none
    Returns: int32_t indicating status of the init operation (0=success, anything else
    indicates an error code)
    */
    int32_t tmp125_init(void);

    /* Description: Read the temperature of the requested temp sensor in degrees C
    Parameters: temp_sensor_id-the id of the temp sensor to read (from 1 to 4)

    p_temp_in_degrees_c-a pointer to a float where the temperature will be
    written

    Returns: int32_t indicating status (0=success, any other value indicates an
    error code)
    */
    int32_t tmp125_read_temp(uint8_t temp_sensor_id, float* p_temp_in_degrees_c);

    float data_word_to_temp(std::vector<uint8_t>& data_word);

protected:
    bool initialized = false;
};
} // namespace tmp_125