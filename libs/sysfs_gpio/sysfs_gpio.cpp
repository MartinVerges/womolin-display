/**
 * @file gpio.cpp
 * @author Martin Verges <martin@verges.cc>
 * @brief Library to handle simple GPIO command on a RPI using the Linux SysFS
 * @version 0.1
 * @date 2022-07-09
 * 
 * @copyright Copyright (c) 2022
 */

#include "sysfs_gpio.h"

SysFS_GPIO::SysFS_GPIO() {};
SysFS_GPIO::~SysFS_GPIO() {};

/**
 * @brief Set the GPIO direction to OUTPUT
 * 
 * @param gpio The GPIO to apply changes to 
 * @return true on success
 * @return false on error
 */
bool SysFS_GPIO::set_direction_out(uint8_t gpio) {
  return set_direction_raw(gpio, "out");
}

/**
 * @brief Set the GPIO direction to INPUT
 * 
 * @param gpio The GPIO to apply changes to 
 * @return true on success
 * @return false on error
 */
bool SysFS_GPIO::set_direction_in(uint8_t gpio) {
  return set_direction_raw(gpio, "in");
}

/**
 * @brief Write raw string to gpio direction (WARNING)
 * 
 * @param gpio The GPIO to apply changes to 
 * @return true on success
 * @return false on error
 */
bool SysFS_GPIO::set_direction_raw(uint8_t gpio, string raw) {
  if (!is_exposed(gpio)) do_export(gpio);

  ofstream out(_path(gpio).append("/direction"));
  if (out) {
    out << raw << endl;
    out.close();
    return true;
  }
  return false;
}

/**
 * @brief Set the output level
 * 
 * @param gpio The GPIO to apply changes to
 * @param level HIGH(true) or LOW(false) value
 */
bool SysFS_GPIO::set_level(uint8_t gpio, uint8_t level) {
  if (!is_exposed(gpio)) do_export(gpio);

  ofstream out(_path(gpio).append("/value"));
  if (out) {
    out << (level ? "1" : "0") << endl;
    out.close();
    return true;
  }
  return false;
}

/**
 * @brief Verify if a GPIO is already exposed under the sysfs
 * 
 * @param gpio to verify
 * @return true when the GPIO is available under sysfs
 * @return false when the GPIO is not exported
 */
bool SysFS_GPIO::is_exposed(uint8_t gpio) {
  ifstream sysfsFile;
  sysfsFile.open(_path(gpio).append("/value"));
  if(sysfsFile) return true;
  else return false;
}

/**
 * @brief Make an GPIO available under the sysfs
 * @param gpio IO port of the CPU
 * 
 * @return true when the GPIO is available under sysfs
 * @return false when the GPIO is not exported
 */
bool SysFS_GPIO::do_export(uint8_t gpio) {
  if (is_exposed(gpio)) return true;

  ofstream out(_base_path().append("/export"));
  out << to_string(gpio) << endl;
  out.close();

  if (is_exposed(gpio)) return true;
  return false;
}

/**
 * @brief Make an GPIO available under the sysfs
 * @param gpio IO port of the CPU
 * 
 * @return true when the GPIO is available under sysfs
 * @return false when the GPIO is not exported
 */
bool SysFS_GPIO::do_unexport(uint8_t gpio) {
  if (!is_exposed(gpio)) return true;

  ofstream out(_base_path().append("/unexport"));
  out << to_string(gpio) << endl;
  out.close();

  if (!is_exposed(gpio)) return true;
  return false;
}

/**
 * @brief Returns the base sysfs path to the GPIO
 * @param gpio the GPIO to return the path to
 */
string SysFS_GPIO::_path(uint8_t gpio) {
  return _base_path().append("/gpio").append(to_string(gpio));
}

