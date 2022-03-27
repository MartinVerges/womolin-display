// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.4
// LVGL VERSION: 8.2
// PROJECT: hud

#ifndef _HUD_UI_H
#define _HUD_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if __has_include("lvgl.h")
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

extern lv_obj_t * ui_MainScreen;
extern lv_obj_t * ui_Navigation;
extern lv_obj_t * ui_NavButton1;
extern lv_obj_t * ui_NavIcon1;
extern lv_obj_t * ui_NavButton2;
extern lv_obj_t * ui_NavIcon2;
extern lv_obj_t * ui_NavButton3;
extern lv_obj_t * ui_NavIcon3;
extern lv_obj_t * ui_NavButton4;
extern lv_obj_t * ui_NavIcon4;
extern lv_obj_t * ui_Content;
extern lv_obj_t * ui_Level;
extern lv_obj_t * ui_LevelMark25;
extern lv_obj_t * ui_LevelMark50;
extern lv_obj_t * ui_LevelMark75;
extern lv_obj_t * ui_LevelIcon;
extern lv_obj_t * ui_LevelState;
extern lv_obj_t * ui_LevelLabel;
extern lv_obj_t * ui_DateIndicator;
extern lv_obj_t * ui_TimeIndicator;
extern lv_obj_t * ui_SettingsButton;

void ONCLICK_NAV_1(lv_event_t * e);
void ONCLICK_NAV_2(lv_event_t * e);
void ONCLICK_NAV_3(lv_event_t * e);
void ONCLICK_NAV_4(lv_event_t * e);
void ONCLICK_SETTINGS(lv_event_t * e);

LV_IMG_DECLARE(ui_img_bg_car_png);    // assets/bg_car.png
LV_IMG_DECLARE(ui_img_icon_weather_active_png);    // assets/icon_weather_active.png
LV_IMG_DECLARE(ui_img_icon_water_inactive_png);    // assets/icon_water_inactive.png
LV_IMG_DECLARE(ui_img_icon_gas_inactive_png);    // assets/icon_gas_inactive.png
LV_IMG_DECLARE(ui_img_icon_battery_inactive_png);    // assets/icon_battery_inactive.png
LV_IMG_DECLARE(ui_img_icon_water_content_png);    // assets/icon_water_content.png
LV_IMG_DECLARE(ui_img_icon_settings_png);    // assets/icon_settings.png


LV_FONT_DECLARE(ui_font_rubik_SemiBold_22);
LV_FONT_DECLARE(ui_font_rubik_bold_53);
LV_FONT_DECLARE(ui_font_rubik_light_18);
LV_FONT_DECLARE(ui_font_rubik_light_40);


void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
