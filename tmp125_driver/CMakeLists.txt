project(tmp125_driver)

include_directories(include)

set(SOURCES src/tmp125_driver.cpp)

add_library(tmp125_driver SHARED ${SOURCES})
target_include_directories(tmp125_driver PUBLIC tmp125_driver/include)


