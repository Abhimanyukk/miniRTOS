add_executable(minirtos_app main.c)
target_link_libraries(minirtos_app minirtos_core minirtos_platform)

add_executable(demo_blink demo_blink/main.c)
target_link_libraries(demo_blink minirtos_core minirtos_platform)

add_executable(demo_tasks demo_tasks/main.c)
target_link_libraries(demo_tasks minirtos_core minirtos_platform)
