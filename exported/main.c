
#define DISP_HOR_RES 1024
#define DISP_VER_RES 600

/*********************
 *      INCLUDES
 *********************/
#define _DEFAULT_SOURCE /* needed for usleep() */
#include <unistd.h>
#define SDL_MAIN_HANDLED /*To fix SDL's "undefined reference to WinMain" issue*/
#include <SDL2/SDL.h>
#include <lvgl.h>
#include <sdl/sdl.h>
#include <display/fbdev.h>
#include <indev/evdev.h>
#include "ui/ui.h"
#include <linux/input.h>
#include <time.h>

/*********************
 *   MQTT-c
 *********************/
#include "src/mqtt_activity.h"
extern struct mqtt_client my_mqtt_client;
static lv_timer_t * timer_mqtt_sync;

/*********************
 *      STATIC VARS
 *********************/
static lv_color_t buf[DISP_HOR_RES * DISP_VER_RES];
static lv_disp_draw_buf_t disp_draw_buf;
static lv_disp_drv_t disp_drv;
static lv_indev_drv_t indev_drv;
static lv_timer_t * timer_upd_clock;

#if USE_EVDEV
static lv_indev_t * indev_touchpad;
#endif

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
void update_clock();
void hal_init_simulator(void);
void hal_init_raspberry(void);


void mqtt_sync_wrapper(lv_timer_t * timer) {
  mqtt_sync(timer->user_data);
}

int main(int argc, char **argv) {
  (void)argc; /* Unused */
  (void)argv; /* Unused */

  /* Initialize LVGL */
  lv_init();

  hal_init_simulator();
  hal_init_raspberry();

  ui_init();

  mqtt_prepare_loop(&my_mqtt_client);

  // Update the clock
  timer_upd_clock = lv_timer_create(update_clock, 500, NULL);
  timer_mqtt_sync = lv_timer_create(mqtt_sync_wrapper, 500, &my_mqtt_client);

  /*Handle LitlevGL tasks (tickless mode)*/
  while(1) {
      lv_tick_inc(5);
      lv_timer_handler();
      usleep(5000);
  }

  return 0;
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

void update_clock() {
	time_t t;
        t = time(NULL);
        struct tm tm;
	tm = *localtime(&t);
	lv_label_set_text_fmt(ui_TimeIndicator, "%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
	lv_label_set_text_fmt(ui_DateIndicator, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
}
