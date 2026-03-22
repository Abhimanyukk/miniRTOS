add_library(minirtos_core
    scheduler/scheduler.c
    logger/logger.c
)

target_include_directories(minirtos_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/config
)

# Core depends on platform.h for function declarations
target_include_directories(minirtos_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../platform
)
