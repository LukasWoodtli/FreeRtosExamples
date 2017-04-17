# EFM32 Emlib CMake file
#
# Configures the emlib and adds it to the build

##### Files #####

# Headers
include_directories(${CMAKE_CURRENT_LIST_DIR})

# Source files
set(COMMON_SOURCES ${CMAKE_CURRENT_LIST_DIR}/low_power_tick_management.c)

##### Outputs #####

# Create emlib library
add_library(commonlib ${COMMON_SOURCES})
target_link_libraries(commonlib ${LIBS})

# Add library to build
set(LIBS ${LIBS} commonlib)

