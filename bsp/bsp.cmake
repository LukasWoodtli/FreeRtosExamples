# BSP CMake file

##### Files #####

# Headers
include_directories(${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/config)

# Source files
FILE(GLOB BSP_SOURCES ${CMAKE_CURRENT_LIST_DIR}/*.c)

##### Outputs #####

# Create emlib library
add_library(bsplib ${BSP_SOURCES})

# Add library to build
set(LIBS ${LIBS} bsplib)
