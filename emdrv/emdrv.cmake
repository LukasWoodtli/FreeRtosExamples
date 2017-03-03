# emdrv CMake file

##### Files #####

# Headers
include_directories(${CMAKE_CURRENT_LIST_DIR}/sleep/inc)

# Source files
FILE(GLOB EMDRV_SOURCES ${CMAKE_CURRENT_LIST_DIR}/sleep/src/*.c)

##### Outputs #####

# Create emlib library
add_library(emdrvlib ${EMDRV_SOURCES})

# Add library to build
set(LIBS ${LIBS} emdrvlib)
