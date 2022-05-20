cmake_minimum_required(VERSION 3.12)

file(GLOB bcm2835_source CONFIGURE_DEPENDS
     "*.h"
     "*.cpp"
     "*.c"
)
add_library(bcm2835 OBJECT ${bcm2835_source})
