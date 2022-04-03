
#define DISP_HOR_RES 1024
#define DISP_VER_RES 600

/*********************
 *   LVGL
 *********************/
#define _DEFAULT_SOURCE   // needed for usleep()
#define SDL_MAIN_HANDLED  // To fix SDL's "undefined reference to WinMain" issue
#include <SDL2/SDL.h>
#include <lvgl.h>
#include <sdl/sdl.h>
#include <display/fbdev.h>
#include <indev/evdev.h>
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

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
int main(int argc, char **argv) {
  (void)argc; /* Unused */
  (void)argv; /* Unused */

  // Load last known configuration
  load_configuration();

  // Initialize LVGL
  lv_init();

  hal_init_simulator();
  hal_init_raspberry();

  ui_init();

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
  timer_mqtt_sync = lv_timer_create(mqtt_sync_wrapper, 500, &mqtt);

  /*Handle LitlevGL tasks (tickless mode)*/
  while(1) {
      lv_tick_inc(5);
      lv_timer_handler();
      usleep(5000);
  }

  return 0;
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
  indev_drv.read_cb = sdl_mouse_read;
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
  indev_drv.read_cb = evdev_read;
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
  if (configuration.freshwater_enabled && strcmp(topic_name, configuration.freshwater_topic.c_str()) == 0) {
    lv_bar_set_value(ui_Level1, atoi(application_message), LV_ANIM_ON);
    lv_label_set_text_fmt(ui_Level1State, "%d%%", atoi(application_message));
  }
  if (configuration.greywater_enabled && strcmp(topic_name, configuration.greywater_topic.c_str()) == 0) {
    lv_bar_set_value(ui_Level2, atoi(application_message), LV_ANIM_ON);
    lv_label_set_text_fmt(ui_Level2State, "%d%%", atoi(application_message));
  }

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
	NAV_BTTN_ENABLE(ui_NavButton1, ui_NavIcon1);
	NAV_BTTN_DISABLE(ui_NavButton2, ui_NavIcon2);
	NAV_BTTN_DISABLE(ui_NavButton3, ui_NavIcon3);
	NAV_BTTN_DISABLE(ui_NavButton4, ui_NavIcon4);
	NAV_BTTN_DISABLE(ui_NavButton5, ui_NavIcon5);
}

void ONCLICK_NAV_2(lv_event_t * e) {
	(void)e;
	NAV_BTTN_DISABLE(ui_NavButton1, ui_NavIcon1);
	NAV_BTTN_ENABLE(ui_NavButton2, ui_NavIcon2);
	NAV_BTTN_DISABLE(ui_NavButton3, ui_NavIcon3);
	NAV_BTTN_DISABLE(ui_NavButton4, ui_NavIcon4);
	NAV_BTTN_DISABLE(ui_NavButton5, ui_NavIcon5);
}

void ONCLICK_NAV_3(lv_event_t * e) {
	(void)e;
	NAV_BTTN_DISABLE(ui_NavButton1, ui_NavIcon1);
	NAV_BTTN_DISABLE(ui_NavButton2, ui_NavIcon2);
	NAV_BTTN_ENABLE(ui_NavButton3, ui_NavIcon3);
	NAV_BTTN_DISABLE(ui_NavButton4, ui_NavIcon4);
	NAV_BTTN_DISABLE(ui_NavButton5, ui_NavIcon5);
}

void ONCLICK_NAV_4(lv_event_t * e) {
	(void)e;
	NAV_BTTN_DISABLE(ui_NavButton1, ui_NavIcon1);
	NAV_BTTN_DISABLE(ui_NavButton2, ui_NavIcon2);
	NAV_BTTN_DISABLE(ui_NavButton3, ui_NavIcon3);
	NAV_BTTN_ENABLE(ui_NavButton4, ui_NavIcon4);
	NAV_BTTN_DISABLE(ui_NavButton5, ui_NavIcon5);
}
void ONCLICK_NAV_5(lv_event_t * e) {
	(void)e;
	NAV_BTTN_DISABLE(ui_NavButton1, ui_NavIcon1);
	NAV_BTTN_DISABLE(ui_NavButton2, ui_NavIcon2);
	NAV_BTTN_DISABLE(ui_NavButton3, ui_NavIcon3);
	NAV_BTTN_DISABLE(ui_NavButton4, ui_NavIcon4);
	NAV_BTTN_ENABLE(ui_NavButton5, ui_NavIcon5);
}
 
void PREFILL_SETTINGS(lv_event_t * e) {
	(void)e;
	lv_textarea_set_text(ui_MqttHost, configuration.mqtt_hostname.c_str());
	lv_textarea_set_text(ui_MqttPort, configuration.mqtt_port.c_str());
	lv_textarea_set_text(ui_MqttUsername, configuration.mqtt_user.c_str());
	lv_textarea_set_text(ui_MqttPassword, configuration.mqtt_pass.c_str());

  switch_state(ui_EnableFreshWater, configuration.freshwater_enabled);
	lv_textarea_set_text(ui_FreshWaterTopic, configuration.freshwater_topic.c_str());

  switch_state(ui_EnableGreyWater, configuration.greywater_enabled);
	lv_textarea_set_text(ui_GreyWaterTopic, configuration.greywater_topic.c_str());
}

void CLOSE_SETTINGS(lv_event_t * e) {
  configuration.mqtt_hostname = lv_textarea_get_text(ui_MqttHost);
  configuration.mqtt_port = lv_textarea_get_text(ui_MqttPort);
  configuration.mqtt_user = lv_textarea_get_text(ui_MqttUsername);
  configuration.mqtt_pass = lv_textarea_get_text(ui_MqttPassword);

  configuration.freshwater_enabled = lv_obj_has_state(ui_EnableFreshWater, LV_STATE_CHECKED);
  configuration.freshwater_topic = lv_textarea_get_text(ui_FreshWaterTopic);
  if (configuration.freshwater_enabled) lv_obj_clear_flag(ui_LevelInfo1, LV_OBJ_FLAG_HIDDEN);

  configuration.greywater_enabled = lv_obj_has_state(ui_EnableGreyWater, LV_STATE_CHECKED);
  configuration.greywater_topic = lv_textarea_get_text(ui_GreyWaterTopic);
  if (configuration.greywater_enabled) lv_obj_clear_flag(ui_LevelInfo2, LV_OBJ_FLAG_HIDDEN);

  save_configuration();
  mqtt_force_reconnect();
}

void LOADSCREEN(lv_event_t * e) {
	(void)e;
	NAV_BTTN_ENABLE(ui_NavButton2, ui_NavIcon2);
  if (!configuration.freshwater_enabled) {  // hide
    lv_obj_add_flag(ui_LevelInfo1, LV_OBJ_FLAG_HIDDEN);
  }
  if (!configuration.greywater_enabled) {  // hide
    lv_obj_add_flag(ui_LevelInfo2, LV_OBJ_FLAG_HIDDEN);
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
