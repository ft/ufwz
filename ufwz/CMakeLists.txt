zephyr_library_named(ufw-zephyr)
add_dependencies(ufw-zephyr ufw)
zephyr_library_sources_ifdef(CONFIG_UFW_SHELL_ADDONS shell-addons.c)
zephyr_include_directories(
  ${UFW_ZEPHYR_ROOT}/include
  ${MICROFRAMEWORK_ROOT}/include)
