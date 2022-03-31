
#define DISP_HOR_RES 1024
#define DISP_VER_RES 600
#define DISP_BUF_SIZE 1024*600/10

/*********************
 *      INCLUDES
 *********************/
#define _DEFAULT_SOURCE /* needed for usleep() */
#include <unistd.h>
#include "lvgl/lvgl.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"
#include "ui/ui.h"
#include <linux/input.h>
#include <time.h>

/*********************
 *      STATIC VARS
 *********************/
static lv_color_t buf[DISP_BUF_SIZE];
static lv_disp_draw_buf_t disp_buf;
static lv_disp_drv_t disp_drv;
static lv_indev_drv_t indev_drv;
static lv_indev_t * indev_touchpad;
static lv_timer_t * timer_upd_clock;

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
void update_clock() {
	time_t t;
        t = time(NULL);
        struct tm tm;
	tm = *localtime(&t);
	lv_label_set_text_fmt(ui_TimeIndicator, "%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
	lv_label_set_text_fmt(ui_DateIndicator, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
}


int main(int argc, char **argv) {
  (void)argc; /* Unused */
  (void)argv; /* Unused */

  /* Initialize LVGL */
  lv_init();

  /* Linux frame buffer device init */
  fbdev_init();

  /* Initialize and register a display driver */
  lv_disp_draw_buf_init(&disp_buf, buf, NULL, DISP_BUF_SIZE);
  lv_disp_drv_init(&disp_drv);
  disp_drv.draw_buf   = &disp_buf;
  disp_drv.flush_cb   = fbdev_flush;
  disp_drv.hor_res    = DISP_HOR_RES;
  disp_drv.ver_res    = DISP_VER_RES;
  lv_disp_drv_register(&disp_drv);

  /* Enable Touchscreen */
  evdev_init();
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = evdev_read;
  indev_touchpad = lv_indev_drv_register(&indev_drv);

  ui_init();

  // Update the clock
  timer_upd_clock = lv_timer_create(update_clock, 500, NULL);

  /*Handle LitlevGL tasks (tickless mode)*/
  while(1) {
      lv_tick_inc(5);
      lv_timer_handler();
      usleep(5000);
  }

  return 0;
}



