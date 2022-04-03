cmake_minimum_required(VERSION 3.19)

include(FetchContent)

# set the project name
project(RV-HUD VERSION 0.1 LANGUAGES C CXX)
add_executable(rv-gui main.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(LV_CONF_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/lv_conf.h
    CACHE STRING "" FORCE)

add_subdirectory(libs)
add_subdirectory(ui)

find_package(SDL2 REQUIRED)

add_compile_options(-Wall -Wextra -pedantic -Werror)
target_link_libraries(rv-gui PRIVATE Ui lvgl lv_drivers mqttc ArduinoJson)

