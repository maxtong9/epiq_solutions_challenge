project(tmp125_driver)


include_directories(include)

set(SOURCES src/tmp125_driver.cpp)

add_library(tmp125_driver SHARED ${SOURCES})
target_include_directories(ptm_lib PUBLIC include)


set (PROJECT_LINK_LIBS libtmp125_driver.so)
# link_directories( ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} )

add_executable(tpm125_driver_main src/main.cpp)
target_link_libraries(tpm125_driver_main ${PROJECT_LINK_LIBS} )

# add_executable(ptm_multi_threaded examples/background_temp_monitor.cpp)
# target_link_libraries(ptm_multi_threaded ${PROJECT_LINK_LIBS})

enable_testing()
