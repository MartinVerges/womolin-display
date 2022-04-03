
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
struct mqtt_reconnect_state_t mqtt_state;
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
void load_configuration(const char *filename, config_t &config) {
  std::fstream fs;
  fs.open (filename, std::fstream::in);

  StaticJsonDocument<4096> doc;
  DeserializationError error = deserializeJson(doc, fs);
  if (error) {
    perror("Failed to read file, using default configuration");
  } 
  config.mqtt_hostname =  doc["mqtt_hostname"] | "localhost";
  config.mqtt_port = doc["mqtt_port"] | "1883";
  config.mqtt_topic = doc["mqtt_topic"] | "test";
  config.mqtt_user = doc["mqtt_user"] | "";
  config.mqtt_pass = doc["mqtt_pass"] | "";
  /*
  cout << "MQTT Hostname = " << config.mqtt_hostname << endl;
  cout << "MQTT Port     = " << config.mqtt_port << endl;
  cout << "MQTT Topic    = " << config.mqtt_topic << endl;
  cout << "MQTT Username = " << config.mqtt_user << endl;
  cout << "MQTT Password = " << config.mqtt_pass << endl;
  */
  fs.close();
}

int main(int argc, char **argv) {
  (void)argc; /* Unused */
  (void)argv; /* Unused */

  // Load last known configuration
  load_configuration(config_filename, configuration);

  // Initialize LVGL
  lv_init();

  hal_init_simulator();
  hal_init_raspberry();

  ui_init();

  mqtt_prepare(&mqtt, configuration);

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

void mqtt_sync_wrapper(lv_timer_t * timer) {
  mqtt_sync(static_cast<mqtt_client*>(timer->user_data));
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
  disp_drv.draw_buf   = &disp_buf;
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
	lv_label_set_text_fmt(ui_DateIndicator, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
}


void mqtt_prepare(struct mqtt_client* client, config_t &config) {
  int bufsize = 2048;
  mqtt_state.client_id = "mydisplay";
  mqtt_state.hostname = config.mqtt_hostname.c_str();
  mqtt_state.port = config.mqtt_port.c_str();
  mqtt_state.topic = config.mqtt_topic.c_str();
  mqtt_state.user = config.mqtt_user.c_str();
  mqtt_state.pass = config.mqtt_pass.c_str();
  mqtt_state.sendbuf = (uint8_t*)malloc(bufsize);
  mqtt_state.sendbufsz = bufsize;
  mqtt_state.recvbuf = (uint8_t*)malloc(bufsize);
  mqtt_state.recvbufsz = bufsize;

  mqtt_init_reconnect(client, mqtt_reconnect_client, &mqtt_state, mqtt_publish_callback);
  printf("%s listening for '%s' messages.\n", mqtt_state.hostname, mqtt_state.topic);
}

void mqtt_reconnect_client(struct mqtt_client* client, void **reconnect_state_vptr) {
  struct mqtt_reconnect_state_t *reconnect_state = *((struct mqtt_reconnect_state_t**) reconnect_state_vptr);

  if (client->error != MQTT_ERROR_INITIAL_RECONNECT) {
    close(client->socketfd);
    printf("reconnect_client: called while client was in error state \"%s\"\n", mqtt_error_str(client->error));

      cout << "MQTT Hostname = " << configuration.mqtt_hostname << endl;
      cout << "MQTT Port     = " << configuration.mqtt_port << endl;
      cout << "MQTT Topic    = " << configuration.mqtt_topic << endl;
      cout << "MQTT Username = " << configuration.mqtt_user << endl;
      cout << "MQTT Password = " << configuration.mqtt_pass << endl;
  }

  int sockfd = open_nb_socket(reconnect_state->hostname, reconnect_state->port);
  if (sockfd == -1) return perror("Failed to open socket!");

  // Reinitialize the client.
  mqtt_reinit(client, sockfd,
              reconnect_state->sendbuf, reconnect_state->sendbufsz,
              reconnect_state->recvbuf, reconnect_state->recvbufsz
  );
  uint8_t connect_flags = MQTT_CONNECT_CLEAN_SESSION;
  mqtt_connect(client, reconnect_state->client_id, NULL, NULL, 0, reconnect_state->user, reconnect_state->pass, connect_flags, 400);
  mqtt_subscribe(client, reconnect_state->topic, 0);
}

void mqtt_publish_callback(void** unused, struct mqtt_response_publish *published) {
  /* note that published->topic_name is NOT null-terminated (here we'll change it to a c-string) */
  char* topic_name = (char*) malloc(published->topic_name_size + 1);
  memcpy(topic_name, published->topic_name, published->topic_name_size);
  topic_name[published->topic_name_size] = '\0';

  char* application_message = (char*) malloc(published->application_message_size + 1);
  memcpy(application_message, published->application_message, published->application_message_size);
  application_message[published->application_message_size] = '\0';
 
  printf("Received publish('%s'): %s\n", topic_name, application_message);
  if (strcmp(topic_name, "freshwater/tanklevel") == 0) {
    lv_bar_set_value(ui_Level1, atoi(application_message), LV_ANIM_ON);
    lv_label_set_text_fmt(ui_Level1State, "%d%%", atoi(application_message));
  }
  printf("Received publish('%s'): %s\n", topic_name, application_message);
  if (strcmp(topic_name, "greywater/tanklevel") == 0) {
    lv_bar_set_value(ui_Level2, atoi(application_message), LV_ANIM_ON);
    lv_label_set_text_fmt(ui_Level2State, "%d%%", atoi(application_message));
  }

  free(topic_name);
  free(application_message);
}
