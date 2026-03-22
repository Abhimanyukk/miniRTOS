cmake_minimum_required(VERSION 3.10)
project(minirtos C)

set(CMAKE_C_STANDARD 99)

# Platform selection: linux (default), esp32, stm32
set(PLATFORM "linux" CACHE STRING "Target platform: linux, esp32, stm32")
set_property(CACHE PLATFORM PROPERTY STRINGS linux esp32 stm32)

# Core library (platform-independent)
add_subdirectory(core)

# Platform abstraction layer
add_subdirectory(platform)

# Demo applications
add_subdirectory(apps)

# Unit tests
enable_testing()
add_subdirectory(tests)
