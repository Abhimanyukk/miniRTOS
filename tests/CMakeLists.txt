# Mock platform library (shared by all unit tests)
add_library(minirtos_mock_platform STATIC mock_platform.c)
target_include_directories(minirtos_mock_platform PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../platform
)

# Scheduler unit test
add_executable(test_scheduler
    unit/test_scheduler.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../core/scheduler/scheduler.c
)
target_link_libraries(test_scheduler minirtos_mock_platform)
target_include_directories(test_scheduler PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../core
    ${CMAKE_CURRENT_SOURCE_DIR}/../core/config
    ${CMAKE_CURRENT_SOURCE_DIR}
)
add_test(NAME test_scheduler COMMAND test_scheduler)

# Logger unit test
add_executable(test_logger
    unit/test_logger.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../core/logger/logger.c
)
target_link_libraries(test_logger minirtos_mock_platform)
target_include_directories(test_logger PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../core
    ${CMAKE_CURRENT_SOURCE_DIR}/../core/config
    ${CMAKE_CURRENT_SOURCE_DIR}
)
add_test(NAME test_logger COMMAND test_logger)
