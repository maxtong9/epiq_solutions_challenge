include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(ptm_unit_test platform_temperature_monitor_unit_test.cpp)

target_link_libraries(ptm_unit_test
 PRIVATE
  GTest::GTest)
  #add lib here)

add_test(ptm_tests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ptm_unit_test)