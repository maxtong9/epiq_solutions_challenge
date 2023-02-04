/**
 * @file platform_temperature_monitor_unit_test.cpp
 * @brief Unit tests for the PlatformTemperatureMonitor class
 * @author Maxton Ginier
 */
#include <gtest/gtest.h>
#include <iostream>
#include "platform_temperature_monitor.hpp"

TEST(PTM, register_temp_sensor)
{
    PTM::PlatformTemperatureMonitor ptm(-100, 100);

    // Register some sensor IDs
    ASSERT_TRUE(ptm.register_temp_sensor(0));
    ASSERT_TRUE(ptm.register_temp_sensor(1));
    ASSERT_TRUE(ptm.register_temp_sensor(25));
    ASSERT_TRUE(ptm.register_temp_sensor(2));
    ASSERT_TRUE(ptm.register_temp_sensor(100));

    // Check that duplicates are rejected
    ASSERT_FALSE(ptm.register_temp_sensor(1));
    ASSERT_FALSE(ptm.register_temp_sensor(100));
}

TEST(PTM, unregister_temp_sensor)
{
    PTM::PlatformTemperatureMonitor ptm(-100, 100);

    uint8_t test = (unsigned int)129;

    std::cout << int(test) << std::endl;
    // Register sensor IDs
    ASSERT_TRUE(ptm.register_temp_sensor(0));
    ASSERT_TRUE(ptm.register_temp_sensor(1));
    ASSERT_TRUE(ptm.register_temp_sensor(25));
    ASSERT_TRUE(ptm.register_temp_sensor(2));

    // Deregister Sensor IDs
    ASSERT_TRUE(ptm.unregister_temp_sensor(0));
    ASSERT_TRUE(ptm.unregister_temp_sensor(1));
    ASSERT_TRUE(ptm.unregister_temp_sensor(25));
    ASSERT_TRUE(ptm.unregister_temp_sensor(2));

    // Check that values were deregistered and returns false if they doesn't exist
    ASSERT_FALSE(ptm.unregister_temp_sensor(0));
    ASSERT_FALSE(ptm.unregister_temp_sensor(1));
    ASSERT_FALSE(ptm.unregister_temp_sensor(25));
    ASSERT_FALSE(ptm.unregister_temp_sensor(2));
    ASSERT_FALSE(ptm.unregister_temp_sensor(100));
}

TEST(PTM, verify_temp_in_range)
{
    PTM::PlatformTemperatureMonitor ptm(-100, 100);

    uint8_t sensor_id = 100;

    // Verify valid temperatures
    ASSERT_TRUE(ptm.verify_temp_in_range(sensor_id, -100));
    ASSERT_TRUE(ptm.verify_temp_in_range(sensor_id, -50));
    ASSERT_TRUE(ptm.verify_temp_in_range(sensor_id, -0));
    ASSERT_TRUE(ptm.verify_temp_in_range(sensor_id, 50));
    ASSERT_TRUE(ptm.verify_temp_in_range(sensor_id, 100));

    // Verify invalid temperatures
    ASSERT_FALSE(ptm.verify_temp_in_range(sensor_id, -101));
    ASSERT_FALSE(ptm.verify_temp_in_range(sensor_id, -500));
    ASSERT_FALSE(ptm.verify_temp_in_range(sensor_id, 101));
    ASSERT_FALSE(ptm.verify_temp_in_range(sensor_id, 500));
}

TEST(PTM, PTM_read_temp)
{
    PTM::PlatformTemperatureMonitor ptm(-100, 100);

    uint8_t sensor_id = 2;
    float test_read = 50;

    // Error Code 0
    ASSERT_EQ(ptm.PTM_read_temp(sensor_id, &test_read), 0);

    // Error Code 1
    sensor_id = 100;
    test_read = 50;
    ASSERT_EQ(ptm.PTM_read_temp(sensor_id, &test_read), 1);
    // Assert float value did not change since Err Code 1
    ASSERT_EQ(test_read, 50);

    // Error Code 1
    sensor_id = 0;
    test_read = 50;
    ASSERT_EQ(ptm.PTM_read_temp(sensor_id, &test_read), 1);
    // Assert float value did not change since Err Code 1
    ASSERT_EQ(test_read, 50);


    // Test Static call & Error Code 0
    sensor_id = 4;
    ASSERT_EQ(PTM::PlatformTemperatureMonitor::PTM_read_temp(sensor_id, &test_read), 0);
}
