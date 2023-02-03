#include <iostream>
#include "tmp125_driver.hpp"
#include "gpio_lib.hpp"

namespace tmp125{

Tmp125Driver::Tmp125Driver()
{
    std::cout << NUM_PINS_PER_PORT << std::endl;
}

int32_t Tmp125Driver::tmp125_init(void)
{
    return 0;
}

int32_t Tmp125Driver::tmp125_read_temp(uint8_t temp_sensor_id, float *p_temp_in_degrees_c)
{
    return 0;
}

} // namespace tmp_125