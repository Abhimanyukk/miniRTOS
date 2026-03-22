if(PLATFORM STREQUAL "linux")
    set(PLATFORM_SRC linux/platform_linux.c)
elseif(PLATFORM STREQUAL "esp32")
    set(PLATFORM_SRC esp32/platform_esp32.c)
elseif(PLATFORM STREQUAL "stm32")
    set(PLATFORM_SRC stm32/platform_stm32.c)
else()
    message(FATAL_ERROR "Unknown PLATFORM: ${PLATFORM}. Use linux, esp32, or stm32.")
endif()

add_library(minirtos_platform ${PLATFORM_SRC})

target_include_directories(minirtos_platform PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

message(STATUS "Building for platform: ${PLATFORM}")
