project(platform_temperature_monitor)

# Set Library aliases
set (LIBTMP libtmp125_driver.so)
set (LIBPTM libptm_lib.so)

# Simple Main PTM Demo code
add_executable(ptm_demo ptm_demo.cpp)
target_link_libraries(ptm_demo ${LIBPTM} )

# Multithreaded PTM Demo Code
add_executable(ptm_demo_multithreaded ptm_demo_multithreaded.cpp)
target_link_libraries(ptm_demo_multithreaded ${LIBPTM})

# Simple Main TMP SW Driver code
add_executable(tmp125_driver_demo tmp125_driver_demo.cpp)
target_link_libraries(tmp125_driver_demo ${LIBTMP} )