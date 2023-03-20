
#define DISP_HOR_RES 1024
#define DISP_VER_RES 600

/*********************
 *   LVGL
 *********************/
#define _DEFAULT_SOURCE   // needed for usleep()
#include "lv_conf.h"
#include "lv_drv_conf.h"
#include <lvgl.h>
#if USE_SDL
#define SDL_MAIN_HANDLED  // To fix SDL's "undefined reference to WinMain" issue
#include <SDL2/SDL.h>
#include <sdl/sdl.h>
#endif
#if USE_FBDEV
#include <display/fbdev.h>
#endif
#if USE_EVDEV
#include <indev/evdev.h>
#endif
#include "ui/ui.h"

/*********************
 *   Mosquitto MQTT
 *********************/
struct mosquitto *mosq;
bool mqtt_is_connected = false;

/*********************
 *   ArduinoJson
 *********************/
#define ARDUINOJSON_ENABLE_STD_STRING 1
#include <ArduinoJson.h>

/*********************
 *   INCLUDES
 *********************/
#include <linux/input.h>
#include <time.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <iostream>
#include "main.h"

using namespace std;

// LVGL
static lv_color_t buf[DISP_HOR_RES * DISP_VER_RES];
static lv_disp_draw_buf_t disp_draw_buf;
static lv_disp_drv_t disp_drv;
static lv_indev_drv_t indev_drv;
#if USE_EVDEV
static lv_indev_t * indev_touchpad;
#endif

// Generic
config_t configuration;
received_mqtt_data_t mqtt_data_cache;


/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void show_warning(const char * message) {
  lv_label_set_text(ui_WarnMessage, message);
  _ui_flag_modify(ui_WarnMessage, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
}

void hide_warning() { 
  if (lv_obj_is_visible(ui_WarnMessage)) {
    _ui_flag_modify(ui_WarnMessage, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
  }
}

void change_display_brightness(uint8_t val) {
  if (display_brightness != val) {
    char charValue[4];
    sprintf(charValue, "%d", val);

    //1 = 100%  255 = 0% brightness in /sys/waveshare/rpi_backlight/brightness
    FILE *out = fopen("/sys/waveshare/rpi_backlight/brightness","w");
    if (out != NULL) {
      fputs(charValue, out);
      fclose(out);
    }
  }
}

void on_mqtt_connect(struct mosquitto *mosq, void *obj, int rc) {
  cout << "[MQTT] on_mqtt_connect(): " << mosquitto_connack_string(rc) << endl;
  if (rc == MOSQ_ERR_SUCCESS) {
    mqtt_is_connected = true;
    if (configuration.freshwater_enabled)  mosquitto_subscribe(mosq, NULL, configuration.freshwater_topic.c_str(), 1);
    if (configuration.greywater_enabled)   mosquitto_subscribe(mosq, NULL, configuration.greywater_topic.c_str(), 1);
    if (configuration.gas_bottle1_enabled) mosquitto_subscribe(mosq, NULL, configuration.gas_bottle1_topic.c_str(), 1);
    if (configuration.gas_bottle2_enabled) mosquitto_subscribe(mosq, NULL, configuration.gas_bottle2_topic.c_str(), 1);
    if (configuration.battery1_enabled)    mosquitto_subscribe(mosq, NULL, configuration.battery1_topic.c_str(), 1);
    if (configuration.battery2_enabled)    mosquitto_subscribe(mosq, NULL, configuration.battery2_topic.c_str(), 1);
  } else {
    cerr << "[MQTT] Error, not going to subscribe topics!" << endl;
  }
}

void on_mqtt_disconnect(struct mosquitto *mosq, void *obj, int rc) {
  mqtt_is_connected = false;
  show_warning("Warning: Not connected to the MQTT");

  if (rc == MOSQ_ERR_SUCCESS) {
    cout << "[MQTT] Successfully disconnected." << endl; 
  } else {
    cerr << "[MQTT] on_mqtt_disconnect(): errno " << rc << " (" << mosquitto_strerror(rc) << ")" << endl;
  }
}

void on_mqtt_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg) {
  cout << "[MQTT] on_mqtt_message(): received update to " << msg->topic << " value " << (char *)msg->payload << endl;
  if (strcmp(msg->topic, configuration.freshwater_topic.c_str()) == 0) {
    mqtt_data_cache.freshwater = atoi((char *)msg->payload);
  } else if (strcmp(msg->topic, configuration.greywater_topic.c_str()) == 0) {
    mqtt_data_cache.greywater = atoi((char *)msg->payload);
  } else if (strcmp(msg->topic, configuration.gas_bottle1_topic.c_str()) == 0) {
    mqtt_data_cache.gas_bottle1 = atoi((char *)msg->payload);
  } else if (strcmp(msg->topic, configuration.gas_bottle2_topic.c_str()) == 0) {
    mqtt_data_cache.gas_bottle2 = atoi((char *)msg->payload);
  } else if (strcmp(msg->topic, configuration.battery1_topic.c_str()) == 0) {
    mqtt_data_cache.battery1 = atoi((char *)msg->payload);
  } else if (strcmp(msg->topic, configuration.battery2_topic.c_str()) == 0) {
    mqtt_data_cache.battery2 = atoi((char *)msg->payload);
  }
  refresh_levels();
}

void mqtt_auto_connect(lv_timer_t *timer) {
  (void)timer;

  if (!mqtt_is_connected) {
    mosquitto_disconnect(mosq);
    mosquitto_loop_stop(mosq, true);

    mosquitto_reinitialise(mosq, NULL, true, NULL);
    mosquitto_connect_callback_set(mosq, on_mqtt_connect);
    mosquitto_disconnect_callback_set(mosq, on_mqtt_disconnect);
    mosquitto_message_callback_set(mosq, on_mqtt_message);

    // ensure that the loop thread is running
    int rc = mosquitto_loop_start(mosq);
    if (rc) {
      cerr << "[MQTT] loop_start failed: " << mosquitto_strerror(rc) << endl;
    } else {
      cout << "[MQTT] Trying to connecting to " << configuration.mqtt_hostname << ":" << configuration.mqtt_port << endl;
      mosquitto_username_pw_set(mosq, configuration.mqtt_user.c_str(), configuration.mqtt_pass.c_str());
      int rc = mosquitto_connect_async(mosq, configuration.mqtt_hostname.c_str(), stoi(configuration.mqtt_port), 5);
      if (rc != MOSQ_ERR_SUCCESS) {
        cerr << "[MQTT] connect_async failed: " << mosquitto_strerror(rc) << endl;
      }
    }
  }
}

int main(int argc, char **argv) {
  (void)argc; // Unused
  (void)argv; // Unused

  // Load last known configuration
  load_configuration();
  change_display_brightness(configuration.display_backlight_max);

  // Initialize LVGL
  lv_init();

  hal_init_simulator();
  hal_init_raspberry();

  ui_init();

#ifndef USE_SDL
  cout << "[GPIO] Using Raspberry PI GPIOs to control relais" << endl;
  gpio.set_level(configuration.relay_1_gpio, GPIO_HIGH);
//  gpio.set_level(configuration.relay_2_gpio, GPIO_HIGH);
//  gpio.set_level(configuration.relay_3_gpio, GPIO_HIGH);
  gpio.set_direction_out(configuration.relay_1_gpio);
//  gpio.set_direction_out(configuration.relay_2_gpio);
//  gpio.set_direction_out(configuration.relay_3_gpio);
#endif

  int rc;
  mosquitto_lib_init();
  mosq = mosquitto_new(NULL, true, NULL); // keep identical to mqtt_auto_connect!
  if (mosq == NULL) {
    cerr << "Error: Out of memory." << endl;
    return EXIT_FAILURE; 
  }
  mqtt_auto_connect(NULL);  // directly try to connect to mqtt

  // Update the clock
  lv_timer_create(display_update_clock, 500, NULL);
  lv_timer_create(mqtt_auto_connect, 30*1000, NULL);

  /*Handle LitlevGL tasks (tickless mode)*/
  while(1) {
    lv_tick_inc(5);
    lv_timer_handler();
    usleep(5000);

    if (mqtt_is_connected) hide_warning();

    // Normal operation (no sleep) 
    if (lv_disp_get_inactive_time(NULL) < configuration.display_backlight_dim_timeout_sec*1000) {
      display_sleep = false;
    } else { // Sleep on inactivity
      display_sleep = true;
      if (configuration.display_backlight_dim_enabled) change_display_brightness(configuration.display_backlight_min);
      // 1 = 100%  255 = 0% brightness in /sys/waveshare/rpi_backlight/brightness
    }
  }

  mosquitto_disconnect(mosq);
  mosquitto_loop_stop(mosq, false);
  mosquitto_destroy(mosq);
  mosquitto_lib_cleanup();
  return 0;
}

void my_input_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data) {
  #if USE_SDL
    sdl_mouse_read(indev_drv, data);
  #endif
  #if USE_EVDEV
    evdev_read(indev_drv, data);
  #endif
  if(configuration.display_backlight_dim_enabled && display_sleep && data->state == LV_INDEV_STATE_PRESSED) {
    change_display_brightness(configuration.display_backlight_max);
  }
}

bool save_configuration() {
  std::fstream fs;
  fs.open (config_filename, std::fstream::out | std::fstream::trunc);
  StaticJsonDocument<4096> doc;
  doc["mqtt_hostname"] = configuration.mqtt_hostname;
  doc["mqtt_port"] = configuration.mqtt_port;
  doc["mqtt_user"] = configuration.mqtt_user;
  doc["mqtt_pass"] = configuration.mqtt_pass;

  doc["freshwater_enabled"] = configuration.freshwater_enabled;
  doc["freshwater_topic"] = configuration.freshwater_topic;
  doc["greywater_enabled"] = configuration.greywater_enabled;
  doc["greywater_topic"] = configuration.greywater_topic;

  doc["gas_bottle1_enabled"] = configuration.gas_bottle1_enabled;
  doc["gas_bottle1_topic"] = configuration.gas_bottle1_topic;
  doc["gas_bottle2_enabled"] = configuration.gas_bottle2_enabled;
  doc["gas_bottle2_topic"] = configuration.gas_bottle2_topic;

  doc["battery1_enabled"] = configuration.battery1_enabled;
  doc["battery1_topic"] = configuration.battery1_topic;
  doc["battery2_enabled"] = configuration.battery2_enabled;
  doc["battery2_topic"] = configuration.battery2_topic;  

  doc["display_backlight_dim_enabled"] = configuration.display_backlight_dim_enabled;
  doc["display_backlight_dim_timeout_sec"] = configuration.display_backlight_dim_timeout_sec;
  doc["display_backlight_max"] = configuration.display_backlight_max;
  doc["display_backlight_min"] = configuration.display_backlight_min;

  doc["relay_1_gpio"] = configuration.relay_1_gpio;
  //doc["relay_2_gpio"] = configuration.relay_2_gpio;
  //doc["relay_3_gpio"] = configuration.relay_3_gpio;

  if (serializeJsonPretty(doc, fs) == 0) {
    perror("Failed to write to file!");
    fs.close();
    return false;
  }
  fs.close();
  return true;
}

void load_configuration() {
  cout << "Loading config file: " << config_filename << endl;
  std::fstream fs;
  fs.open (config_filename, std::fstream::in);

  StaticJsonDocument<4096> doc;
  DeserializationError error = deserializeJson(doc, fs);
  if (error) {
    perror("Failed to read file, using default configuration");
  }
  configuration.mqtt_hostname =  doc["mqtt_hostname"] | "localhost";
  configuration.mqtt_port = doc["mqtt_port"] | "1883";
  configuration.mqtt_user = doc["mqtt_user"] | "";
  configuration.mqtt_pass = doc["mqtt_pass"] | "";

  configuration.freshwater_enabled = doc["freshwater_enabled"] | false;
  configuration.freshwater_topic = doc["freshwater_topic"] | "waterlevel/level1";
  configuration.greywater_enabled = doc["greywater_enabled"] | false;
  configuration.greywater_topic = doc["greywater_topic"] | "waterlevel/level2";

  configuration.gas_bottle1_enabled = doc["gas_bottle1_enabled"] | false;
  configuration.gas_bottle1_topic = doc["gas_bottle1_topic"] | "gaslevel/level1";
  configuration.gas_bottle2_enabled = doc["gas_bottle2_enabled"] | false;
  configuration.gas_bottle2_topic = doc["gas_bottle2_topic"] | "gaslevel/level2";

  configuration.battery1_enabled = doc["battery1_enabled"] | false;
  configuration.battery1_topic = doc["battery1_topic"] | "battery1/soc";
  configuration.battery2_enabled = doc["battery2_enabled"] | false;
  configuration.battery2_topic = doc["battery2_topic"] | "battery2/soc";

  configuration.display_backlight_dim_enabled = doc["display_backlight_dim_enabled"] | true;
  configuration.display_backlight_dim_timeout_sec = doc["display_backlight_dim_timeout_sec"] | 15;
  configuration.display_backlight_max = doc["display_backlight_max"] | 1;
  configuration.display_backlight_min = doc["display_backlight_min"] | 255;

  configuration.relay_1_gpio = doc["relay_1_gpio"] | 26;
//  configuration.relay_2_gpio = doc["relay_2_gpio"] | 20;
//  configuration.relay_3_gpio = doc["relay_3_gpio"] | 21;

  fs.close();
}

void hal_init_simulator(void) {
#if USE_SDL
  /* Use the 'monitor' driver which creates window on PC's monitor to simulate a display*/
  sdl_init();

  /*Create a display buffer*/
  lv_disp_draw_buf_init(&disp_draw_buf, buf, NULL, SDL_HOR_RES * SDL_VER_RES);

  /*Create a display*/
  lv_disp_drv_init(&disp_drv); /*Basic initialization*/
  disp_drv.draw_buf = &disp_draw_buf;
  disp_drv.flush_cb = sdl_display_flush;
  disp_drv.hor_res = SDL_HOR_RES;
  disp_drv.ver_res = SDL_VER_RES;
  lv_disp_drv_register(&disp_drv);

  /* Add a mouse as input device */
  lv_indev_drv_init(&indev_drv); /*Basic initialization*/
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_input_read;
  lv_indev_drv_register(&indev_drv);
#endif
}

void hal_init_raspberry(void) {
#if USE_FBDEV
  /* Linux frame buffer device init */
  fbdev_init();

  /* Initialize and register a display driver */
  lv_disp_draw_buf_init(&disp_draw_buf, buf, NULL, DISP_HOR_RES * DISP_VER_RES);
  lv_disp_drv_init(&disp_drv);
  disp_drv.draw_buf   = &disp_draw_buf;
  disp_drv.flush_cb   = fbdev_flush;
  disp_drv.hor_res    = DISP_HOR_RES;
  disp_drv.ver_res    = DISP_VER_RES;
  lv_disp_drv_register(&disp_drv);
#endif

#if USE_EVDEV
  /* Enable Touchscreen */
  evdev_init();
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_input_read;
  indev_touchpad = lv_indev_drv_register(&indev_drv);
#endif
}

void display_update_clock(lv_timer_t *timer) {
  time_t t;
  t = time(NULL);
  struct tm tm;
  tm = *localtime(&t);
  lv_label_set_text_fmt(ui_TimeIndicator, "%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
  lv_label_set_text_fmt(ui_DateIndicator, "%02d.%02d.%04d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
}

void set_level(uint8_t num, int level) {
  if (num == 1) {
    lv_bar_set_value(ui_Level1, level, LV_ANIM_ON);
    lv_label_set_text_fmt(ui_Level1State, "%d%%", level);
  } else if (num == 2) {
    lv_bar_set_value(ui_Level2, level, LV_ANIM_ON);
    lv_label_set_text_fmt(ui_Level2State, "%d%%", level);
  }
}

void refresh_levels() {
  switch (nav_screen) {
    case 2: // Water
      set_level(1, mqtt_data_cache.freshwater);
      set_level(2, mqtt_data_cache.greywater);
    break;
    case 3: // Battery
      set_level(1, mqtt_data_cache.battery1);
      set_level(2, mqtt_data_cache.battery2);
    break;
    case 4: // Gas
      set_level(1, mqtt_data_cache.gas_bottle1);
      set_level(2, mqtt_data_cache.gas_bottle2);
    break;
    default:
      printf("Unknown screen");
    break;
  }  
}

/*********************
 *   LVGL related
 *********************/
void NAV_BTTN_ENABLE(lv_obj_t * bttn, lv_obj_t * icon) {
  lv_obj_set_style_bg_color(bttn, lv_color_hex(0x2DAB66), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_grad_dir(bttn, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_img_recolor(icon, lv_color_hex(0x141414), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_img_recolor_opa(icon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
}
void NAV_BTTN_DISABLE(lv_obj_t * bttn, lv_obj_t * icon) {
  lv_obj_set_style_bg_color(bttn, lv_color_hex(0x141414), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_grad_dir(bttn, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_img_recolor(icon, lv_color_hex(0x888888), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_img_recolor_opa(icon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void ONCLICK_NAV_1(lv_event_t * e) {
  (void)e;
  nav_screen = 1;
  //NAV_BTTN_ENABLE(ui_NavButton1, ui_NavIcon1);
  NAV_BTTN_DISABLE(ui_NavButton2, ui_NavIcon2);
  NAV_BTTN_DISABLE(ui_NavButton3, ui_NavIcon3);
  NAV_BTTN_DISABLE(ui_NavButton4, ui_NavIcon4);
  //NAV_BTTN_DISABLE(ui_NavButton5, ui_NavIcon5);
  refresh_levels();
}

void ONCLICK_NAV_2(lv_event_t * e) {  // Tanklevel
  (void)e;
  nav_screen = 2;
  //NAV_BTTN_DISABLE(ui_NavButton1, ui_NavIcon1);
  NAV_BTTN_ENABLE(ui_NavButton2, ui_NavIcon2);
  NAV_BTTN_DISABLE(ui_NavButton3, ui_NavIcon3);
  NAV_BTTN_DISABLE(ui_NavButton4, ui_NavIcon4);
  //NAV_BTTN_DISABLE(ui_NavButton5, ui_NavIcon5);

  lv_label_set_text(ui_Level1Label, "FRESH WATER");
  lv_label_set_text(ui_Level2Label, "GREY WATER");
  lv_img_set_src(ui_Level1Icon, &ui_img_icon_water_content_clean_png);
  lv_img_set_src(ui_Level2Icon, &ui_img_icon_water_content_dirty_png);

  if (configuration.freshwater_enabled) lv_obj_clear_flag(ui_LevelInfo1, LV_OBJ_FLAG_HIDDEN);
  else lv_obj_add_flag(ui_LevelInfo1, LV_OBJ_FLAG_HIDDEN);
  if (configuration.greywater_enabled) lv_obj_clear_flag(ui_LevelInfo2, LV_OBJ_FLAG_HIDDEN);
  else lv_obj_add_flag(ui_LevelInfo2, LV_OBJ_FLAG_HIDDEN);
  refresh_levels();
}

void ONCLICK_NAV_3(lv_event_t * e) {  // Battery
  (void)e;
  nav_screen = 3;
  //NAV_BTTN_DISABLE(ui_NavButton1, ui_NavIcon1);
  NAV_BTTN_DISABLE(ui_NavButton2, ui_NavIcon2);
  NAV_BTTN_ENABLE(ui_NavButton3, ui_NavIcon3);
  NAV_BTTN_DISABLE(ui_NavButton4, ui_NavIcon4);
  //NAV_BTTN_DISABLE(ui_NavButton5, ui_NavIcon5);

  lv_label_set_text(ui_Level1Label, "BATTERY 1");
  lv_label_set_text(ui_Level2Label, "BATTERY 2");
  lv_img_set_src(ui_Level1Icon, &ui_img_icon_battery_large_png);
  lv_img_set_src(ui_Level2Icon, &ui_img_icon_battery_large_png);

  if (configuration.battery1_enabled) lv_obj_clear_flag(ui_LevelInfo1, LV_OBJ_FLAG_HIDDEN);
  else lv_obj_add_flag(ui_LevelInfo1, LV_OBJ_FLAG_HIDDEN);
  if (configuration.battery2_enabled) lv_obj_clear_flag(ui_LevelInfo2, LV_OBJ_FLAG_HIDDEN);
  else lv_obj_add_flag(ui_LevelInfo2, LV_OBJ_FLAG_HIDDEN);
  refresh_levels();
}

void ONCLICK_NAV_4(lv_event_t * e) {  // Gas
  (void)e;
  nav_screen = 4;
  //NAV_BTTN_DISABLE(ui_NavButton1, ui_NavIcon1);
  NAV_BTTN_DISABLE(ui_NavButton2, ui_NavIcon2);
  NAV_BTTN_DISABLE(ui_NavButton3, ui_NavIcon3);
  NAV_BTTN_ENABLE(ui_NavButton4, ui_NavIcon4);
  //NAV_BTTN_DISABLE(ui_NavButton5, ui_NavIcon5);

  lv_label_set_text(ui_Level1Label, "BOTTLE 1");
  lv_label_set_text(ui_Level2Label, "BOTTLE 2");
  lv_img_set_src(ui_Level1Icon, &ui_img_icon_gas_large_png);
  lv_img_set_src(ui_Level2Icon, &ui_img_icon_gas_large_png);

  if (configuration.gas_bottle1_enabled) lv_obj_clear_flag(ui_LevelInfo1, LV_OBJ_FLAG_HIDDEN);
  else lv_obj_add_flag(ui_LevelInfo1, LV_OBJ_FLAG_HIDDEN);
  if (configuration.gas_bottle2_enabled) lv_obj_clear_flag(ui_LevelInfo2, LV_OBJ_FLAG_HIDDEN);
  else lv_obj_add_flag(ui_LevelInfo2, LV_OBJ_FLAG_HIDDEN);
  refresh_levels();
}

void ONCLICK_NAV_5(lv_event_t * e) {
  (void)e;
  nav_screen = 5;
  //NAV_BTTN_DISABLE(ui_NavButton1, ui_NavIcon1);
  NAV_BTTN_DISABLE(ui_NavButton2, ui_NavIcon2);
  NAV_BTTN_DISABLE(ui_NavButton3, ui_NavIcon3);
  NAV_BTTN_DISABLE(ui_NavButton4, ui_NavIcon4);
  //NAV_BTTN_ENABLE(ui_NavButton5, ui_NavIcon5);
  refresh_levels();
}
 
void PREFILL_SETTINGS(lv_event_t * e) {
  (void)e;
  char charValue[32]; // temp to display numbers

  lv_textarea_set_text(ui_MqttHost, configuration.mqtt_hostname.c_str());
  lv_textarea_set_text(ui_MqttPort, configuration.mqtt_port.c_str());
  lv_textarea_set_text(ui_MqttUsername, configuration.mqtt_user.c_str());
  lv_textarea_set_text(ui_MqttPassword, configuration.mqtt_pass.c_str());

  switch_state(ui_EnableFreshWater, configuration.freshwater_enabled);
  lv_textarea_set_text(ui_FreshWaterTopic, configuration.freshwater_topic.c_str());
  switch_state(ui_EnableGreyWater, configuration.greywater_enabled);
  lv_textarea_set_text(ui_GreyWaterTopic, configuration.greywater_topic.c_str());

  switch_state(ui_EnableGas1, configuration.gas_bottle1_enabled);
  lv_textarea_set_text(ui_GasTopic1, configuration.gas_bottle1_topic.c_str());
  switch_state(ui_EnableGas2, configuration.gas_bottle2_enabled);
  lv_textarea_set_text(ui_GasTopic2, configuration.gas_bottle2_topic.c_str());

  switch_state(ui_EnableBattery1, configuration.battery1_enabled);
  lv_textarea_set_text(ui_BatteryTopic1, configuration.battery1_topic.c_str());
  switch_state(ui_EnableBattery2, configuration.battery2_enabled);
  lv_textarea_set_text(ui_BatteryTopic2, configuration.battery2_topic.c_str());
  
  switch_state(ui_DisplayDimEnable, configuration.display_backlight_dim_enabled);
  sprintf(charValue, "%d", configuration.display_backlight_dim_timeout_sec);
  lv_textarea_set_text(ui_DisplayDimTimeout, charValue); 
  sprintf(charValue, "%d", configuration.display_backlight_max);
  lv_textarea_set_text(ui_DisplayBacklightMax, charValue); 
  sprintf(charValue, "%d", configuration.display_backlight_min);
  lv_textarea_set_text(ui_DisplayBacklightMin, charValue); 

  sprintf(charValue, "%d", configuration.relay_1_gpio);
  lv_textarea_set_text(ui_Relay1GPIO, charValue); 
/*  sprintf(charValue, "%d", configuration.relay_2_gpio);
  lv_textarea_set_text(ui_Relay2GPIO, charValue); 
  sprintf(charValue, "%d", configuration.relay_3_gpio);
  lv_textarea_set_text(ui_Relay3GPIO, charValue); 
  */
}

void CLOSE_SETTINGS(lv_event_t * e) {
  configuration.mqtt_hostname = lv_textarea_get_text(ui_MqttHost);
  configuration.mqtt_port = lv_textarea_get_text(ui_MqttPort);
  configuration.mqtt_user = lv_textarea_get_text(ui_MqttUsername);
  configuration.mqtt_pass = lv_textarea_get_text(ui_MqttPassword);

  configuration.freshwater_enabled = lv_obj_has_state(ui_EnableFreshWater, LV_STATE_CHECKED);
  configuration.freshwater_topic = lv_textarea_get_text(ui_FreshWaterTopic);
  configuration.greywater_enabled = lv_obj_has_state(ui_EnableGreyWater, LV_STATE_CHECKED);
  configuration.greywater_topic = lv_textarea_get_text(ui_GreyWaterTopic);

  configuration.gas_bottle1_enabled = lv_obj_has_state(ui_EnableGas1, LV_STATE_CHECKED);
  configuration.gas_bottle1_topic = lv_textarea_get_text(ui_GasTopic1);
  configuration.gas_bottle2_enabled = lv_obj_has_state(ui_EnableGas2, LV_STATE_CHECKED);
  configuration.gas_bottle2_topic = lv_textarea_get_text(ui_GasTopic2);

  configuration.battery1_enabled = lv_obj_has_state(ui_EnableBattery1, LV_STATE_CHECKED);
  configuration.battery1_topic = lv_textarea_get_text(ui_BatteryTopic1);
  configuration.battery2_enabled = lv_obj_has_state(ui_EnableBattery2, LV_STATE_CHECKED);
  configuration.battery2_topic = lv_textarea_get_text(ui_BatteryTopic2);

  configuration.display_backlight_dim_enabled = lv_obj_has_state(ui_DisplayDimEnable, LV_STATE_CHECKED);
  configuration.display_backlight_dim_timeout_sec = atoi(lv_textarea_get_text(ui_DisplayDimTimeout));
  configuration.display_backlight_max = atoi(lv_textarea_get_text(ui_DisplayBacklightMax));
  configuration.display_backlight_min = atoi(lv_textarea_get_text(ui_DisplayBacklightMin));

  configuration.relay_1_gpio = atoi(lv_textarea_get_text(ui_Relay1GPIO));
  //configuration.relay_2_gpio = atoi(lv_textarea_get_text(ui_Relay2GPIO));
  //configuration.relay_3_gpio = atoi(lv_textarea_get_text(ui_Relay3GPIO));

  save_configuration();
  mosquitto_disconnect(mosq);
  mqtt_auto_connect(NULL);
  ONCLICK_NAV_2(e);
}

void LOADSCREEN(lv_event_t * e) {
  ONCLICK_NAV_2(e);
}

void RELAY_1(lv_event_t * e) {
  cout << "[UI] " << "Relay 1 - status change" << endl;
#ifndef USE_SDL
  if (lv_obj_has_state(ui_Relay1, LV_STATE_CHECKED)) {
    gpio.set_level(configuration.relay_1_gpio, GPIO_LOW);
  } else {
    gpio.set_level(configuration.relay_1_gpio, GPIO_HIGH);
  }
#endif
}
/*
void RELAY_2(lv_event_t * e) {
#ifndef USE_SDL
  if (lv_obj_has_state(ui_Relay2, LV_STATE_CHECKED)) {
    gpio.set_level(configuration.relay_2_gpio, GPIO_LOW);
  } else {
    gpio.set_level(configuration.relay_2_gpio, GPIO_HIGH);
  }
#endif
}
void RELAY_3(lv_event_t * e) {
#ifndef USE_SDL
  if (lv_obj_has_state(ui_Relay3, LV_STATE_CHECKED)) {
    gpio.set_level(configuration.relay_3_gpio, GPIO_LOW);
  } else {
    gpio.set_level(configuration.relay_3_gpio, GPIO_HIGH);
  }
#endif
}
*/