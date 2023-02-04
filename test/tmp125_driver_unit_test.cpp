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

TEST(TMP125_driver, data_word_to_temp)
{
    Tmp125Driver tmp125;
    // Bits sourced from the TMP 125 spec sheet
    std::vector<uint8_t> data_word_127{0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0}; // 127
    std::vector<uint8_t> data_word_125{0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0}; // 125
    std::vector<uint8_t> data_word_25{0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}; // 25
    std::vector<uint8_t> data_word_10{0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}; // 10
    std::vector<uint8_t> data_word_f25{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}; // 0.25
    std::vector<uint8_t> data_word_0{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // 0
    std::vector<uint8_t> data_word_fneg25{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0}; // -0.25
    std::vector<uint8_t> data_word_neg25{0, 1, 1, 1, 0 ,0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0}; // -25

    ASSERT_EQ(tmp125.data_word_to_temp(data_word_127), 127);
    ASSERT_EQ(tmp125.data_word_to_temp(data_word_125), 125);
    ASSERT_EQ(tmp125.data_word_to_temp(data_word_25), 25);
    ASSERT_EQ(tmp125.data_word_to_temp(data_word_10), 10);
    ASSERT_EQ(tmp125.data_word_to_temp(data_word_f25), 0.25);
    ASSERT_EQ(tmp125.data_word_to_temp(data_word_0), 0);
    ASSERT_EQ(tmp125.data_word_to_temp(data_word_fneg25), -0.25);
    ASSERT_EQ(tmp125.data_word_to_temp(data_word_neg25), -25);



    
    
}
