# Add project sources
set(SOURCES
  main.c
	low_power_tick_management.c
)

##### Outputs #####

# Generate executable and link
add_executable(${TARGET} ${SOURCES})

target_link_libraries(${TARGET} ${LIBS})

