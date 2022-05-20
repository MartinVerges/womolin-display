
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
 *   MQTT-c
 *********************/
#include <mqtt.h>
#include "posix_sockets.h"
#include <stdlib.h>

/*********************
 *   ArduinoJson
 *********************/
#define ARDUINOJSON_ENABLE_STD_STRING 1
#include <ArduinoJson.h>

/*********************
 *   BCM2835
 *********************/
#include "bcm2835.h"
bool use_bcm2835 = false;

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

// MQTT-c
struct mqtt_client mqtt;
struct mqtt_buffer_t mqtt_state;
static lv_timer_t * timer_mqtt_sync;

// LVGL
static lv_color_t buf[DISP_HOR_RES * DISP_VER_RES];
static lv_disp_draw_buf_t disp_draw_buf;
static lv_disp_drv_t disp_drv;
static lv_indev_drv_t indev_drv;
static lv_timer_t * timer_upd_clock;
#if USE_EVDEV
static lv_indev_t * indev_touchpad;
#endif

// Generic
config_t configuration;
received_mqtt_data_t mqtt_data_cache;


/**********************
 *   GLOBAL FUNCTIONS
 **********************/
void change_display_brightness(uint8_t val) {
  if (display_brightness != val) {
    char charValue[3];
    sprintf(charValue, "%d", val);

    //1 = 100%  255 = 0% brightness in /sys/waveshare/rpi_backlight/brightness
    FILE *out = fopen("/sys/waveshare/rpi_backlight/brightness","w");
    if (out != NULL) {
      fputs(charValue, out);
      fclose(out);
    }
  }
}

int main(int argc, char **argv) {
  (void)argc; /* Unused */
  (void)argv; /* Unused */

  // Load last known configuration
  load_configuration();
  change_display_brightness(configuration.display_backlight_max);

  // Initialize LVGL
  lv_init();

  hal_init_simulator();
  hal_init_raspberry();

  ui_init();

  if (bcm2835_init() ) {
    use_bcm2835 = true;
    printf("[BCM2835] Init success");
    bcm2835_gpio_fsel(configuration.relay_1_gpio, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(configuration.relay_2_gpio, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(configuration.relay_3_gpio, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_delay(100); // on boot, release all relais
    bcm2835_gpio_write(configuration.relay_1_gpio, HIGH);
    bcm2835_gpio_write(configuration.relay_2_gpio, HIGH);
    bcm2835_gpio_write(configuration.relay_3_gpio, HIGH);
  }

  // Allways allocate the memory on startup. We will never free it up again!
  int bufsize = 2048;
  mqtt_state.sendbuf = (uint8_t*)malloc(bufsize);
  mqtt_state.sendbufsz = bufsize;
  mqtt_state.recvbuf = (uint8_t*)malloc(bufsize);
  mqtt_state.recvbufsz = bufsize;
  cout << "[MQTT] Connecting to " << configuration.mqtt_hostname << ":" << configuration.mqtt_port << endl;
  mqtt_init_reconnect(&mqtt, mqtt_reconnect_client, &mqtt_state, mqtt_publish_callback);

  // Update the clock
  timer_upd_clock = lv_timer_create(display_update_clock, 500, NULL);
  timer_mqtt_sync = lv_timer_create(mqtt_sync_wrapper, 2500, &mqtt);

  /*Handle LitlevGL tasks (tickless mode)*/
  while(1) {
    lv_tick_inc(5);
    lv_timer_handler();
    usleep(5000);

    // Normal operation (no sleep) 
    if (lv_disp_get_inactive_time(NULL) < configuration.display_backlight_dim_timeout_sec*1000) {
      display_sleep = false;
    } else { // Sleep on inactivity
      display_sleep = true;
      if (configuration.display_backlight_dim_enabled) change_display_brightness(configuration.display_backlight_min);
      // 1 = 100%  255 = 0% brightness in /sys/waveshare/rpi_backlight/brightness
    }
  }

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

  if (serializeJsonPretty(doc, fs) == 0) {
    perror("Failed to write to file!");
    fs.close();
    return false;
  }
  fs.close();
  return true;
}

void load_configuration() {
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
  configuration.freshwater_topic = doc["freshwater_topic"] | "freshwater/tanklevel";
  configuration.greywater_enabled = doc["greywater_enabled"] | false;
  configuration.greywater_topic = doc["greywater_topic"] | "greywater/tanklevel";

  configuration.gas_bottle1_enabled = doc["gas_bottle1_enabled"] | false;
  configuration.gas_bottle1_topic = doc["gas_bottle1_topic"] | "gas/bottle1";
  configuration.gas_bottle2_enabled = doc["gas_bottle2_enabled"] | false;
  configuration.gas_bottle2_topic = doc["gas_bottle2_topic"] | "gas/bottle2";

  configuration.battery1_enabled = doc["battery1_enabled"] | false;
  configuration.battery1_topic = doc["battery1_topic"] | "battery1/soc";
  configuration.battery2_enabled = doc["battery2_enabled"] | false;
  configuration.battery2_topic = doc["battery2_topic"] | "battery2/soc";

  configuration.display_backlight_dim_enabled = doc["display_backlight_dim_enabled"] | true;
  configuration.display_backlight_dim_timeout_sec = doc["display_backlight_dim_timeout_sec"] | 15;
  configuration.display_backlight_max = doc["display_backlight_max"] | 1;
  configuration.display_backlight_min = doc["display_backlight_min"] | 255;

  configuration.relay_1_gpio = doc["relay_1_gpio"] | 26;
  configuration.relay_2_gpio = doc["relay_2_gpio"] | 20;
  configuration.relay_3_gpio = doc["relay_3_gpio"] | 21;

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

/*********************
 *   MQTT related
 *********************/
void mqtt_sync_wrapper(lv_timer_t * timer) {
  mqtt_sync(static_cast<mqtt_client*>(timer->user_data));
}

void mqtt_force_reconnect() {
  mqtt.error = MQTT_ERROR_CONNECTION_CLOSED;
}

void mqtt_reconnect_client(struct mqtt_client* client, void **reconnect_state_vptr) {
  struct mqtt_buffer_t *reconnect_state = *((struct mqtt_buffer_t**) reconnect_state_vptr);

  if (client->error != MQTT_ERROR_INITIAL_RECONNECT) {
    close(client->socketfd);
    printf("reconnect_client: called while client was in error state \"%s\"\n", mqtt_error_str(client->error));
  }

  int sockfd = open_nb_socket(configuration.mqtt_hostname.c_str(), configuration.mqtt_port.c_str());
  if (sockfd == -1) return perror("Failed to open socket!");

  // Reinitialize the client.
  mqtt_reinit(client, sockfd,
              reconnect_state->sendbuf, reconnect_state->sendbufsz,
              reconnect_state->recvbuf, reconnect_state->recvbufsz
  );
  uint8_t connect_flags = MQTT_CONNECT_CLEAN_SESSION;
  mqtt_connect(client, "mydisplay", NULL, NULL, 0, configuration.mqtt_user.c_str(), configuration.mqtt_pass.c_str(), connect_flags, 400);

  if (configuration.freshwater_enabled) mqtt_subscribe(client, configuration.freshwater_topic.c_str(), 0);
  if (configuration.greywater_enabled) mqtt_subscribe(client, configuration.greywater_topic.c_str(), 0);
  if (configuration.gas_bottle1_enabled) mqtt_subscribe(client, configuration.gas_bottle1_topic.c_str(), 0);
  if (configuration.gas_bottle2_enabled) mqtt_subscribe(client, configuration.gas_bottle2_topic.c_str(), 0);
  if (configuration.battery1_enabled) mqtt_subscribe(client, configuration.battery1_topic.c_str(), 0);
  if (configuration.battery2_enabled) mqtt_subscribe(client, configuration.battery2_topic.c_str(), 0);
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

void mqtt_publish_callback(void** unused, struct mqtt_response_publish *published) {
  /* note that published->topic_name is NOT null-terminated (here we'll change it to a c-string) */
  char* topic_name = (char*) malloc(published->topic_name_size + 1);
  memcpy(topic_name, published->topic_name, published->topic_name_size);
  topic_name[published->topic_name_size] = '\0';

  char* application_message = (char*) malloc(published->application_message_size + 1);
  memcpy(application_message, published->application_message, published->application_message_size);
  application_message[published->application_message_size] = '\0';
 
  // FIXME: get rid of c_str()
  printf("Received publish('%s'): %s\n", topic_name, application_message);
  if (strcmp(topic_name, configuration.freshwater_topic.c_str()) == 0) {
    mqtt_data_cache.freshwater = atoi(application_message);
  } else if (strcmp(topic_name, configuration.greywater_topic.c_str()) == 0) {
    mqtt_data_cache.greywater = atoi(application_message);
  } else if (strcmp(topic_name, configuration.gas_bottle1_topic.c_str()) == 0) {
    mqtt_data_cache.gas_bottle1 = atoi(application_message);
  } else if (strcmp(topic_name, configuration.gas_bottle2_topic.c_str()) == 0) {
    mqtt_data_cache.gas_bottle2 = atoi(application_message);
  } else if (strcmp(topic_name, configuration.battery1_topic.c_str()) == 0) {
    mqtt_data_cache.battery1 = atoi(application_message);
  } else if (strcmp(topic_name, configuration.battery2_topic.c_str()) == 0) {
    mqtt_data_cache.battery2 = atoi(application_message);
  }

  refresh_levels();
  free(topic_name);
  free(application_message);
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
  NAV_BTTN_ENABLE(ui_NavButton1, ui_NavIcon1);
  NAV_BTTN_DISABLE(ui_NavButton2, ui_NavIcon2);
  NAV_BTTN_DISABLE(ui_NavButton3, ui_NavIcon3);
  NAV_BTTN_DISABLE(ui_NavButton4, ui_NavIcon4);
  NAV_BTTN_DISABLE(ui_NavButton5, ui_NavIcon5);
  refresh_levels();
}

void ONCLICK_NAV_2(lv_event_t * e) {  // Tanklevel
  (void)e;
  nav_screen = 2;
  NAV_BTTN_DISABLE(ui_NavButton1, ui_NavIcon1);
  NAV_BTTN_ENABLE(ui_NavButton2, ui_NavIcon2);
  NAV_BTTN_DISABLE(ui_NavButton3, ui_NavIcon3);
  NAV_BTTN_DISABLE(ui_NavButton4, ui_NavIcon4);
  NAV_BTTN_DISABLE(ui_NavButton5, ui_NavIcon5);

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
  NAV_BTTN_DISABLE(ui_NavButton1, ui_NavIcon1);
  NAV_BTTN_DISABLE(ui_NavButton2, ui_NavIcon2);
  NAV_BTTN_ENABLE(ui_NavButton3, ui_NavIcon3);
  NAV_BTTN_DISABLE(ui_NavButton4, ui_NavIcon4);
  NAV_BTTN_DISABLE(ui_NavButton5, ui_NavIcon5);

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
  NAV_BTTN_DISABLE(ui_NavButton1, ui_NavIcon1);
  NAV_BTTN_DISABLE(ui_NavButton2, ui_NavIcon2);
  NAV_BTTN_DISABLE(ui_NavButton3, ui_NavIcon3);
  NAV_BTTN_ENABLE(ui_NavButton4, ui_NavIcon4);
  NAV_BTTN_DISABLE(ui_NavButton5, ui_NavIcon5);

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
  NAV_BTTN_DISABLE(ui_NavButton1, ui_NavIcon1);
  NAV_BTTN_DISABLE(ui_NavButton2, ui_NavIcon2);
  NAV_BTTN_DISABLE(ui_NavButton3, ui_NavIcon3);
  NAV_BTTN_DISABLE(ui_NavButton4, ui_NavIcon4);
  NAV_BTTN_ENABLE(ui_NavButton5, ui_NavIcon5);
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

  save_configuration();
  mqtt_force_reconnect();
  ONCLICK_NAV_2(e);
}

void LOADSCREEN(lv_event_t * e) {
  ONCLICK_NAV_2(e);
}

void RELAY_1(lv_event_t * e) {
  if (!use_bcm2835) return;  
  if (lv_obj_has_state(ui_Relay1, LV_STATE_CHECKED)) {
    bcm2835_gpio_write(configuration.relay_1_gpio, LOW);
  } else {
    bcm2835_gpio_write(configuration.relay_1_gpio, HIGH);
  }
}
void RELAY_2(lv_event_t * e) {
  if (!use_bcm2835) return;
  if (lv_obj_has_state(ui_Relay2, LV_STATE_CHECKED)) {
    bcm2835_gpio_write(configuration.relay_2_gpio, LOW);
  } else {
    bcm2835_gpio_write(configuration.relay_2_gpio, HIGH);
  }
}
void RELAY_3(lv_event_t * e) {
  if (!use_bcm2835) return;
  if (lv_obj_has_state(ui_Relay3, LV_STATE_CHECKED)) {
    bcm2835_gpio_write(configuration.relay_3_gpio, LOW);
  } else {
    bcm2835_gpio_write(configuration.relay_3_gpio, HIGH);
  }
}

/*void NAV_BTTN_ACTIVE() {
  lv_obj_t * parent;
  lv_obj_t * child;
  for(int i1 = 0; i1 < lv_obj_get_child_cnt(ui_Settings); i1++) {
    parent  = lv_obj_get_child(ui_Settings, i1);
    if (lv_obj_check_type(parent, &lv_obj_class)) {
      for(int i2 = 0; i2 < lv_obj_get_child_cnt(parent); i2++) {
        child = lv_obj_get_child(parent, i2);
        if (lv_obj_check_type(child, &lv_switch_class)) {
          LV_LOG_INFO("Activating Switch");
          lv_obj_add_state(child, LV_STATE_CHECKED);
        } else if (lv_obj_check_type(child, &lv_textarea_class)) {
        }
        
      }
    }
  }
}*/
