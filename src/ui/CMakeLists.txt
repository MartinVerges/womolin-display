cmake_minimum_required(VERSION 3.12)

file(GLOB ui_sources CONFIGURE_DEPENDS
     "*.h"
     "*.cpp"
     "*.c"
)
add_library(Ui OBJECT ${ui_sources})

find_package(SDL2 REQUIRED)
target_link_libraries(Ui PRIVATE SDL2 lvgl lv_drivers)
