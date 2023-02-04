project(platform_temperature_monitor)
# Set Library aliases
set (LIBTMP libtmp125_driver.so)
set (LIBPTM libptm_lib.so)

# Simple Main PTM Demo code
add_executable(ptm_driver ptm_driver.cpp)
target_link_libraries(ptm_driver ${LIBPTM} )

# Multithreaded PTM Demo Code
add_executable(ptm_multi_threaded background_temp_monitor.cpp)
target_link_libraries(ptm_multi_threaded ${LIBPTM})

# Simple Main TMP SW Driver code
add_executable(tpm125_driver_main main.cpp)
target_link_libraries(tpm125_driver_main ${LIBTMP} )