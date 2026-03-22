cmake_minimum_required(VERSION 3.10)
project(minirtos C)

set(CMAKE_C_STANDARD 99)

# Platform selection: linux (default), esp32, stm32
set(PLATFORM "linux" CACHE STRING "Target platform: linux, esp32, stm32")
set_property(CACHE PLATFORM PROPERTY STRINGS linux esp32 stm32)

# Core library (platform-independent)
add_library(minirtos_core
    core/scheduler/scheduler.c
    core/logger/logger.c
)
target_include_directories(minirtos_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/platform
)

# Platform library
if(PLATFORM STREQUAL "linux")
    add_library(minirtos_platform platform/linux/platform_linux.c)
elseif(PLATFORM STREQUAL "esp32")
    add_library(minirtos_platform platform/esp32/platform_esp32.c)
elseif(PLATFORM STREQUAL "stm32")
    add_library(minirtos_platform platform/stm32/platform_stm32.c)
else()
    message(FATAL_ERROR "Unknown PLATFORM: ${PLATFORM}. Use linux, esp32, or stm32.")
endif()

message(STATUS "Building for platform: ${PLATFORM}")

target_include_directories(minirtos_platform PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/platform
)

# Main app (empty main for testing the library)
add_executable(minirtos_app apps/main.c)
target_link_libraries(minirtos_app minirtos_core minirtos_platform)

# Demo: blink
add_executable(demo_blink apps/demo_blink/main.c)
target_link_libraries(demo_blink minirtos_core minirtos_platform)

# Demo: tasks
add_executable(demo_tasks apps/demo_tasks/main.c)
target_link_libraries(demo_tasks minirtos_core minirtos_platform)
