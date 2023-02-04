#include <gtest/gtest.h>
#include "tmp125_driver.hpp"
#include <array>
using namespace tmp125;

TEST(TMP125_driver, tmp125_init)
{
    Tmp125Driver tmp125;
    
    // Test initializing with no errors
    ASSERT_EQ(tmp125.tmp125_init(), 0);

}

TEST(TMP125_driver, tmp125_read_temp)
{
    Tmp125Driver tmp125;
    std::array<uint8_t, 4> valid_ids{1, 2, 3, 4};
    std::array<uint8_t, 4> invalid_ids{86, 0, 5, 100};
    float dummy_float_val;

    // Test error codes before initialization
    ASSERT_EQ(tmp125.tmp125_read_temp(valid_ids[0], &dummy_float_val), 2);
    ASSERT_EQ(tmp125.tmp125_read_temp(invalid_ids[0], &dummy_float_val), 2);

    tmp125.tmp125_init();

    // Test valid IDs
    for (uint8_t id : valid_ids)
    {
        
        ASSERT_EQ(tmp125.tmp125_read_temp(id, &dummy_float_val), 0);
    }
    
    // Test invalid IDs
    for (uint8_t id : invalid_ids)
    {
        float dummy_float_val;
        ASSERT_EQ(tmp125.tmp125_read_temp(id, &dummy_float_val), 1);
    }
}

TEST(TMP125_driver, data_word_to_temperature)
{
    Tmp125Driver tmp125;

    // Values to test (source: TMP spec sheet)
    uint32_t data_word_127 = 0b011111110000000;
    uint32_t data_word_75 = 0b010010110000000;
    uint32_t data_word_f25 = 0b000000000100000;
    uint32_t data_word_0 = 0x0;
    uint32_t data_word_neg_f25 = 0b111111111100000;
    uint32_t data_word_neg_55 = 0b110010010000000;

    ASSERT_EQ(tmp125.data_word_to_temperature(data_word_127), 127);
    ASSERT_EQ(tmp125.data_word_to_temperature(data_word_75), 75);
    ASSERT_EQ(tmp125.data_word_to_temperature(data_word_f25), 0.25);
    ASSERT_EQ(tmp125.data_word_to_temperature(data_word_0), 0);
    ASSERT_EQ(tmp125.data_word_to_temperature(data_word_neg_f25), -0.25);
    ASSERT_EQ(tmp125.data_word_to_temperature(data_word_neg_55), -55);
}
