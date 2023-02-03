#include <gtest/gtest.h>
#include <iostream>
#include "platform_temperature_monitor.hpp"
TEST(test1, testname)
{
    PTM::PlatformTemperatureMonitor ptm(-100, 100);
    std::cout << "Hello, World" << std::endl;
    ASSERT_EQ(1, 2);
}