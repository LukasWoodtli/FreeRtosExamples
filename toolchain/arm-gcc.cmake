# ARM none eabi gcc toolchain configuration
# Copyright (c) 2016 Ryan Kurte
# This file is covered under the MIT license available at: https://opensource.org/licenses/MIT

# We are cross compiling so we don't want compiler tests to run, as they will fail
include(CMakeForceCompiler)

# Indicate we aren't compiling for an OS
set(CMAKE_SYSTEM_NAME Generic)

# Set processor type
set(CMAKE_SYSTEM_PROCESSOR arm)

# taken from https://github.com/MOSAIC-LoPoW/dash7-ap-open-source-stack/blob/master/stack/cmake/toolchains/gcc-arm-embedded.cmake
set(CMAKE_C_COMPILER   "arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "arm-none-eabi-g++")
# without these cmake tries to compile/link a test and fails on _exit
# this _was_ suppressed by the now deprecated FORCE versions
set(CMAKE_C_COMPILER_WORKS   1)
set(CMAKE_CXX_COMPILER_WORKS 1)

set(CMAKE_ASM_COMPILER ${COMPILER_PREFIX}arm-none-eabi-g++)

# pathes to search other tools
set(TOOLS_SEARCH_PATHS
  $ENV{PATH}
  ${COMPILER_PREFIX}
  /usr/local/gcc_arm/gcc-arm-none-eabi-5_4-2016q3/bin/ # my installation path on OS X
)


# Set other tools
FIND_PROGRAM(OBJSIZE arm-none-eabi-size
  PATHS
  ${TOOLS_SEARCH_PATHS}
)


FIND_PROGRAM(OBJCOPY arm-none-eabi-objcopy
  PATHS
  ${TOOLS_SEARCH_PATHS}
)


FIND_PROGRAM(OBJDUMP arm-none-eabi-objdump
  PATHS
  ${TOOLS_SEARCH_PATHS}
)

FIND_PROGRAM(DEBUGGER arm-none-eabi-gdb
  PATHS
  ${TOOLS_SEARCH_PATHS}
)

# Remove preset linker flags
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "") 
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "") 
set(CMAKE_SHARED_LIBRARY_LINK_ASM_FLAGS "")

# Set library options
set(SHARED_LIBS OFF)
set(STATIC_LIBS ON)
