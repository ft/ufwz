zephyr_library_named(ufw-zephyr)
add_dependencies(ufw-zephyr ufw)
zephyr_library_sources(shell-addons.c)
zephyr_include_directories(
  ${UFW_ZEPHYR_ROOT}
  ${MICROFRAMEWORK_ROOT}/include)
