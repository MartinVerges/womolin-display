cmake_minimum_required(VERSION 3.12)

file(GLOB sysfs_gpio_source CONFIGURE_DEPENDS
     "*.h"
     "*.cpp"
     "*.c"
)
add_library(sysfs_gpio OBJECT ${sysfs_gpio_source})
