

#include "mosquitto.h"
#include <lvgl.h>
#include <string>
#include <sysfs_gpio.h>

using namespace std;

SysFS_GPIO gpio;

int nav_screen = 1;

bool display_sleep = false;
uint8_t display_brightness = 0;
void change_display_brightness(uint8_t val);

const char* config_filename = "config.json";
struct config_t {
  string mqtt_hostname;
  string mqtt_port;
  string mqtt_user;
  string mqtt_pass;

  bool freshwater_enabled;
  string freshwater_topic;
  bool greywater_enabled;
  string greywater_topic;

  bool gas_bottle1_enabled;
  string gas_bottle1_topic;
  bool gas_bottle2_enabled;
  string gas_bottle2_topic;

  bool battery1_enabled;
  string battery1_topic;
  bool battery2_enabled;
  string battery2_topic;

  bool display_backlight_dim_enabled;
  uint16_t display_backlight_dim_timeout_sec;
  uint8_t display_backlight_max;
  uint8_t display_backlight_min;

  uint8_t relay_1_gpio;
  uint8_t relay_2_gpio;
  uint8_t relay_3_gpio;
};
void load_configuration();
bool save_configuration();

void display_update_clock(lv_timer_t *timer);

void hal_init_simulator(void);
void hal_init_raspberry(void);

void set_level(lv_obj_t * bar, lv_obj_t * label, int level);
void refresh_levels();

struct received_mqtt_data_t {
  uint8_t freshwater;
  uint8_t greywater;

  uint8_t gas_bottle1;
  uint8_t gas_bottle2;

  uint8_t battery1;
  uint8_t battery2;
};

#define Relay_Ch1 26
#define Relay_Ch2 20
#define Relay_Ch3 21
