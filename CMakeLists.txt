cmake_minimum_required(VERSION 3.10)
project(minirtos C)

set(CMAKE_C_STANDARD 99)

# Core library (platform-independent)
add_library(minirtos_core
    core/scheduler/scheduler.c
    core/logger/logger.c
)
target_include_directories(minirtos_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/platform
)

# Platform library (Linux)
add_library(minirtos_platform
    platform/linux/platform_linux.c
)
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
