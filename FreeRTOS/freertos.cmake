# FreeRTOS CMake file

##### Files #####

# Headers
include_directories(${CMAKE_CURRENT_LIST_DIR}
	${CMAKE_CURRENT_LIST_DIR}/basic_io 
	${CMAKE_CURRENT_LIST_DIR}/Source/include 
	${CMAKE_CURRENT_LIST_DIR}/Source/portable/GCC/ARM_CM3)

# Source files
FILE(GLOB_RECURSE FREERTOS_SOURCES ${CMAKE_CURRENT_LIST_DIR}/*.c)

set(FREERTOS_MEM_MANG  ${CMAKE_CURRENT_LIST_DIR}/Source/portable/MemMang/heap_1.c)
##### Outputs #####

# Create emlib library
add_library(freertoslib ${FREERTOS_SOURCES} ${FREERTOS_MEM_MANG})

# Add library to build
set(LIBS ${LIBS} freertoslib)
