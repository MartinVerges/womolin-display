cmake_minimum_required(VERSION 3.18)

project(display VERSION 0.1 LANGUAGES C CXX)

add_compile_options(-static)
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true) 
set(CMAKE_CXX_CPPLINT true)

set(LV_BUILD_EXAMPLES false)

include_directories(${CMAKE_SOURCE_DIR}/libs/sysfs_gpio/)

add_subdirectory(${CMAKE_SOURCE_DIR}/libs/sysfs_gpio/)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/)
