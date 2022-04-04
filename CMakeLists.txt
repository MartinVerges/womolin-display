cmake_minimum_required(VERSION 3.18)

include(FetchContent)
include(ExternalProject)

# set the project name
project(RV-HUD VERSION 0.1 LANGUAGES C CXX)
add_executable(rv-gui main.cpp)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/archive)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(LV_CONF_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/lv_conf.h
    CACHE STRING "" FORCE)

FetchContent_Declare(lvgl        GIT_REPOSITORY https://github.com/lvgl/lvgl                 GIT_TAG v8.2.0)
FetchContent_Declare(lv_drivers  GIT_REPOSITORY https://github.com/lvgl/lv_drivers           GIT_TAG v8.2.0)
FetchContent_Declare(mqttc       GIT_REPOSITORY https://github.com/LiamBindle/MQTT-C.git     GIT_TAG 1.1.5)
FetchContent_Declare(ArduinoJson GIT_REPOSITORY https://github.com/bblanchon/ArduinoJson.git GIT_TAG v6.19.3)
FetchContent_MakeAvailable(lvgl lv_drivers mqttc ArduinoJson)

add_subdirectory(ui)

find_package(SDL2 REQUIRED)

add_compile_options(-Wall -Wextra -pedantic -Werror)
target_link_libraries(rv-gui PRIVATE Ui lvgl lv_drivers mqttc ArduinoJson)

install(FILES rv-gui PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ DESTINATION /usr/lib/rv-hud/bin/)
install(FILES ${CMAKE_SOURCE_DIR}/systemd/rv-hud.service DESTINATION /etc/systemd/system/)
install(CODE "EXECUTE_PROCESS(COMMAND systemctl daemon-reload)")
install(CODE "EXECUTE_PROCESS(COMMAND systemctl stop rv-hud.service)")
install(CODE "EXECUTE_PROCESS(COMMAND systemctl enable --now rv-hud.service)")
