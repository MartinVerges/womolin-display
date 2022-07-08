cmake_minimum_required(VERSION 3.18)

include(FetchContent)
include(ExternalProject)

# set the project name
add_executable(display main.cpp)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/archive)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(LV_CONF_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/lv_conf.h
    CACHE STRING "" FORCE)

FetchContent_Declare(lvgl        GIT_REPOSITORY https://github.com/lvgl/lvgl                 GIT_TAG v8.2.0)
FetchContent_Declare(lv_drivers  GIT_REPOSITORY https://github.com/lvgl/lv_drivers           GIT_TAG v8.2.0)
FetchContent_Declare(ArduinoJson GIT_REPOSITORY https://github.com/bblanchon/ArduinoJson.git GIT_TAG v6.19.3)
FetchContent_MakeAvailable(lvgl lv_drivers ArduinoJson)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ui)

find_package(SDL2 REQUIRED)

add_compile_options(-Wall -Wextra -pedantic -Werror)
target_link_libraries(display PRIVATE Ui lvgl lv_drivers mosquitto ArduinoJson bcm2835)

install(FILES ${CMAKE_BINARY_DIR}/src/display PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ DESTINATION /usr/lib/womolin-display/bin/)
install(FILES ${CMAKE_SOURCE_DIR}/systemd/womolin-display.service DESTINATION /etc/systemd/system/)
install(CODE "EXECUTE_PROCESS(COMMAND systemctl daemon-reload)")
install(CODE "EXECUTE_PROCESS(COMMAND systemctl stop womolin-display.service)")
install(CODE "EXECUTE_PROCESS(COMMAND systemctl enable --now womolin-display.service)")

