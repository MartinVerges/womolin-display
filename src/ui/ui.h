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
#include "ui_helpers.h"

extern lv_obj_t * ui_MainScreen;
extern lv_obj_t * ui_Content;
extern lv_obj_t * ui_LevelInfo1;
extern lv_obj_t * ui_Level1;
extern lv_obj_t * ui_Level1Mark25;
extern lv_obj_t * ui_Level1Mark50;
extern lv_obj_t * ui_Level1Mark75;
extern lv_obj_t * ui_Level1Icon;
extern lv_obj_t * ui_Level1State;
extern lv_obj_t * ui_Level1Label;
extern lv_obj_t * ui_LevelInfo2;
extern lv_obj_t * ui_Level2;
extern lv_obj_t * ui_Level2Mark25;
extern lv_obj_t * ui_Level2Mark50;
extern lv_obj_t * ui_Level2Mark75;
extern lv_obj_t * ui_Level2Icon;
extern lv_obj_t * ui_Level2State;
extern lv_obj_t * ui_Level2Label;
extern lv_obj_t * ui_DateIndicator;
extern lv_obj_t * ui_TimeIndicator;
extern lv_obj_t * ui_ButtonSettingsOpen;
extern lv_obj_t * ui_Navigation;
//extern lv_obj_t * ui_NavButton1;
//extern lv_obj_t * ui_NavIcon1;
extern lv_obj_t * ui_NavButton2;
extern lv_obj_t * ui_NavIcon2;
extern lv_obj_t * ui_NavButton3;
extern lv_obj_t * ui_NavIcon3;
extern lv_obj_t * ui_NavButton4;
extern lv_obj_t * ui_NavIcon4;
//extern lv_obj_t * ui_NavButton5;
//extern lv_obj_t * ui_NavIcon5;
extern lv_obj_t * ui_Settings;
extern lv_obj_t * ui_ButtonSettingsClose;
extern lv_obj_t * ui_Keyboard;
extern lv_obj_t * ui_MqttConnection;
extern lv_obj_t * ui_MqttEnabled;
extern lv_obj_t * ui_MqttServerLabel;
extern lv_obj_t * ui_MqttHost;
extern lv_obj_t * ui_MqttPort;
extern lv_obj_t * ui_MqttUsername;
extern lv_obj_t * ui_MqttPassword;
extern lv_obj_t * ui_FreshWaterLevel;
extern lv_obj_t * ui_EnableFreshWater;
extern lv_obj_t * ui_FreshWaterLabel;
extern lv_obj_t * ui_FreshWaterTopic;
extern lv_obj_t * ui_GreyWaterLevel;
extern lv_obj_t * ui_EnableGreyWater;
extern lv_obj_t * ui_GreyWaterLabel;
extern lv_obj_t * ui_GreyWaterTopic;
extern lv_obj_t * ui_GasSensors;
extern lv_obj_t * ui_GasLabel1;
extern lv_obj_t * ui_EnableGas1;
extern lv_obj_t * ui_EnableGas2;
extern lv_obj_t * ui_GasTopic1;
extern lv_obj_t * ui_GasTopic2;
extern lv_obj_t * ui_BatterySensors;
extern lv_obj_t * ui_BatteryLabel1;
extern lv_obj_t * ui_EnableBattery1;
extern lv_obj_t * ui_EnableBattery2;
extern lv_obj_t * ui_BatteryTopic1;
extern lv_obj_t * ui_BatteryTopic2;
extern lv_obj_t * ui_Display;
extern lv_obj_t * ui_DisplayLabel;
extern lv_obj_t * ui_DisplayDimEnable;
extern lv_obj_t * ui_DisplayDimTimeout;
extern lv_obj_t * ui_DisplayBacklightMax;
extern lv_obj_t * ui_DisplayBacklightMin;
extern lv_obj_t * ui_Relays;
extern lv_obj_t * ui_Relay1;
extern lv_obj_t * ui_Relay1Label;
/*
extern lv_obj_t * ui_Relay2;
extern lv_obj_t * ui_Relay2Label;
extern lv_obj_t * ui_Relay3;
extern lv_obj_t * ui_Relay3Label;
*/
extern lv_obj_t * ui_RelaysSettings;
extern lv_obj_t * ui_RelaysLabel;
extern lv_obj_t * ui_Relay1GPIO;
//extern lv_obj_t * ui_Relay2GPIO;
//extern lv_obj_t * ui_Relay3GPIO;
extern lv_obj_t * ui_WarnMessage;



void NAV_BTTN_ENABLE(lv_obj_t * bttn, lv_obj_t * icon);
void NAV_BTTN_DISABLE(lv_obj_t * bttn, lv_obj_t * icon);
void ONCLICK_NAV_1(lv_event_t * e);
void ONCLICK_NAV_2(lv_event_t * e);
void ONCLICK_NAV_3(lv_event_t * e);
void ONCLICK_NAV_4(lv_event_t * e);
void ONCLICK_NAV_5(lv_event_t * e);
void PREFILL_SETTINGS(lv_event_t * e);
void CLOSE_SETTINGS(lv_event_t * e);
void LOADSCREEN(lv_event_t * e);
void RELAY_1(lv_event_t * e);
void RELAY_2(lv_event_t * e);
void RELAY_3(lv_event_t * e);

void switch_state(lv_obj_t * obj, bool state);

LV_IMG_DECLARE(ui_img_bg_car_png)               // assets/bg_car.png
LV_IMG_DECLARE(ui_img_icon_water_content_clean_png)    // assets/icon_water_content_clean.png
LV_IMG_DECLARE(ui_img_icon_water_content_dirty_png)    // assets/icon_water_content_dirty.png
LV_IMG_DECLARE(ui_img_icon_settings_png)        // assets/icon_settings.png
LV_IMG_DECLARE(ui_img_icon_weather_png)         // assets/icon_weather.png
LV_IMG_DECLARE(ui_img_icon_water_png)           // assets/icon_water.png
LV_IMG_DECLARE(ui_img_icon_battery_png)         // assets/icon_battery.png
LV_IMG_DECLARE(ui_img_icon_battery_large_png)         // assets/icon_battery_large.png
LV_IMG_DECLARE(ui_img_icon_gas_png)             // assets/icon_gas.png
LV_IMG_DECLARE(ui_img_icon_gas_large_png);      // assets/icon_gas_large.png
LV_IMG_DECLARE(ui_img_icon_temperature_png)     // assets/icon_temperature.png
LV_IMG_DECLARE(ui_img_bg_png)                   // assets/bg.png
LV_IMG_DECLARE(ui_img_icon_close_png)           // assets/icon_close.png

LV_FONT_DECLARE(ui_font_rubik_SemiBold_22)
LV_FONT_DECLARE(ui_font_rubik_bold_53)
LV_FONT_DECLARE(ui_font_rubik_light_18)
LV_FONT_DECLARE(ui_font_rubik_light_40)

void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
