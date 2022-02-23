set(UFW_ZEPHYR_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
add_subdirectory_ifdef(CONFIG_UFW_ZEPHYR ufwz)
