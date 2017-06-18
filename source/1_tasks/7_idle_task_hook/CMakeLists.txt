
# Configure project and languages
set(TARGET IdleTaskHook)

project(${TARGET} C CXX ASM)

# Add project sources
set(SOURCES
  main.c
  low_power_tick_management.c  # vApplicationIdleHook removed (implement own version)
  ${CMAKE_CURRENT_LIST_DIR}/../../common/print.c
)

##### Outputs #####

# defining own idle task hook which is otherwise defined in low_power_tick_management.c
# so the library is removed
list(REMOVE_ITEM LIBS commonlib)



# Generate executable and link
add_executable(${TARGET} ${SOURCES})

target_link_libraries(${TARGET} ${LIBS})

include(${CMAKE_CURRENT_LIST_DIR}/../../../toolchain/post-build.cmake)

source_group("src" FILES ${SOURCES})

