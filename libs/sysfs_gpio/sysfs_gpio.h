/**
 * @file gpio.cpp
 * @author Martin Verges <martin@verges.cc>
 * @brief Library to handle simple GPIO command on a RPI using the Linux SysFS
 * @version 0.1
 * @date 2022-07-09
 * 
 * @copyright Copyright (c) 2022
 */

#ifndef SYSFS_GPIO_h
#define SYSFS_GPIO_h

#include <string>
#include <fstream>

using namespace std;

#define GPIO_HIGH 1
#define GPIO_LOW 0

class SysFS_GPIO {
  public:
    SysFS_GPIO();
    virtual ~SysFS_GPIO();

    bool set_level(uint8_t gpio, uint8_t level);
    bool set_direction_out(uint8_t gpio);
    bool set_direction_in(uint8_t gpio);
    bool is_exposed(uint8_t gpio);
    bool do_export(uint8_t gpio);
    bool do_unexport(uint8_t gpio);

  private:
    // we want to get a new instance of string() on each request
    inline string _base_path() { return string("/sys/class/gpio"); };
    string _path(uint8_t gpio);
    bool set_direction_raw(uint8_t gpio, string raw);
};

#endif
