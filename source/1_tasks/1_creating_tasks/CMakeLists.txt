# Add project sources
set(SOURCES
  main.c
	low_power_tick_management.c
)

##### Outputs #####

# Generate executable and link
add_executable(${TARGET} ${SOURCES})

target_link_libraries(${TARGET} ${LIBS})

include(${CMAKE_CURRENT_LIST_DIR}/../../../toolchain/post-build.cmake)

source_group("src" FILES ${SOURCES})

