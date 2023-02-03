namespace tmp125{
class Tmp125Driver
{
public:    
    Tmp125Driver();

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
};
} // namespace tmp_125