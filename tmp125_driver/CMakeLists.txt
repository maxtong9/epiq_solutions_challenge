project(tmp125_driver)

include_directories(include)

set(SOURCES src/tmp125_driver.cpp src/spi_interface.cpp)

add_library(tmp125_driver SHARED ${SOURCES})
target_include_directories(tmp125_driver PUBLIC tmp125_driver/include)


