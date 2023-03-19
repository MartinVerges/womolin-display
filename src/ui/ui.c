#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_MainScreen;
lv_obj_t * ui_Content;
lv_obj_t * ui_LevelInfo1;
lv_obj_t * ui_Level1;
lv_obj_t * ui_Level1Mark25;
lv_obj_t * ui_Level1Mark50;
lv_obj_t * ui_Level1Mark75;
lv_obj_t * ui_Level1Icon;
lv_obj_t * ui_Level1State;
lv_obj_t * ui_Level1Label;
lv_obj_t * ui_LevelInfo2;
lv_obj_t * ui_Level2;
lv_obj_t * ui_Level2Mark25;
lv_obj_t * ui_Level2Mark50;
lv_obj_t * ui_Level2Mark75;
lv_obj_t * ui_Level2Icon;
lv_obj_t * ui_Level2State;
lv_obj_t * ui_Level2Label;
lv_obj_t * ui_DateIndicator;
lv_obj_t * ui_TimeIndicator;
lv_obj_t * ui_ButtonSettingsOpen;
lv_obj_t * ui_Navigation;
//lv_obj_t * ui_NavButton1;
//lv_obj_t * ui_NavIcon1;
lv_obj_t * ui_NavButton2;
lv_obj_t * ui_NavIcon2;
lv_obj_t * ui_NavButton3;
lv_obj_t * ui_NavIcon3;
lv_obj_t * ui_NavButton4;
lv_obj_t * ui_NavIcon4;
//lv_obj_t * ui_NavButton5;
//lv_obj_t * ui_NavIcon5;
lv_obj_t * ui_Settings;
lv_obj_t * ui_ButtonSettingsClose;
lv_obj_t * ui_Keyboard;
lv_obj_t * ui_MqttConnection;
lv_obj_t * ui_MqttServerLabel;
lv_obj_t * ui_MqttHost;
lv_obj_t * ui_MqttPort;
lv_obj_t * ui_MqttUsername;
lv_obj_t * ui_MqttPassword;
lv_obj_t * ui_FreshWaterLevel;
lv_obj_t * ui_EnableFreshWater;
lv_obj_t * ui_FreshWaterLabel;
lv_obj_t * ui_FreshWaterTopic;
lv_obj_t * ui_GreyWaterLevel;
lv_obj_t * ui_EnableGreyWater;
lv_obj_t * ui_GreyWaterLabel;
lv_obj_t * ui_GreyWaterTopic;
lv_obj_t * ui_GasSensors;
lv_obj_t * ui_GasLabel1;
lv_obj_t * ui_EnableGas1;
lv_obj_t * ui_EnableGas2;
lv_obj_t * ui_GasTopic1;
lv_obj_t * ui_GasTopic2;
lv_obj_t * ui_BatterySensors;
lv_obj_t * ui_BatteryLabel1;
lv_obj_t * ui_EnableBattery1;
lv_obj_t * ui_EnableBattery2;
lv_obj_t * ui_BatteryTopic1;
lv_obj_t * ui_BatteryTopic2;
lv_obj_t * ui_Display;
lv_obj_t * ui_DisplayLabel;
lv_obj_t * ui_DisplayDimEnable;
lv_obj_t * ui_DisplayDimTimeout;
lv_obj_t * ui_DisplayBacklightMax;
lv_obj_t * ui_DisplayBacklightMin;
lv_obj_t * ui_Relays;
lv_obj_t * ui_Relay1;
lv_obj_t * ui_Relay1Label;
lv_obj_t * ui_Relay2;
lv_obj_t * ui_Relay2Label;
lv_obj_t * ui_Relay3;
lv_obj_t * ui_Relay3Label;
lv_obj_t * ui_RelaysSettings;
lv_obj_t * ui_RelaysLabel;
lv_obj_t * ui_Relay1GPIO;
lv_obj_t * ui_Relay2GPIO;
lv_obj_t * ui_Relay3GPIO;
lv_obj_t * ui_WarnMessage;

///////////////////// FUNCTIONS ////////////////////
static void ui_event_MainScreen(lv_event_t * e) {
    if(lv_event_get_code(e) == LV_EVENT_SCREEN_LOADED) LOADSCREEN(e);
}
static void ui_event_ButtonSettingsOpen(lv_event_t * e) {
    if(lv_event_get_code(e) == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_Settings, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0);
    }
}
static void ui_event_NavButton1(lv_event_t * e) {
    if(lv_event_get_code(e) == LV_EVENT_CLICKED) ONCLICK_NAV_1(e);
}
static void ui_event_NavButton2(lv_event_t * e) {
    if(lv_event_get_code(e) == LV_EVENT_CLICKED) ONCLICK_NAV_2(e);
}
static void ui_event_NavButton3(lv_event_t * e) {
    if(lv_event_get_code(e) == LV_EVENT_CLICKED) ONCLICK_NAV_3(e);
}
static void ui_event_NavButton4(lv_event_t * e) {
    if(lv_event_get_code(e) == LV_EVENT_CLICKED) ONCLICK_NAV_4(e);
}
static void ui_event_NavButton5(lv_event_t * e) {
    if(lv_event_get_code(e) == LV_EVENT_CLICKED) ONCLICK_NAV_5(e);
}
static void ui_event_Settings(lv_event_t * e) {
    if(lv_event_get_code(e) == LV_EVENT_SCREEN_LOAD_START) PREFILL_SETTINGS(e);
}
static void ui_event_ButtonSettingsClose(lv_event_t * e) {
    if(lv_event_get_code(e) == LV_EVENT_CLICKED) {
        _ui_screen_change(ui_MainScreen, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0);
        CLOSE_SETTINGS(e);
    }
}
static void ui_event_relay_1(lv_event_t * e) {
    if(lv_event_get_code(e) == LV_EVENT_VALUE_CHANGED) RELAY_1(e);
}
static void ui_event_relay_2(lv_event_t * e) {
    if(lv_event_get_code(e) == LV_EVENT_VALUE_CHANGED) RELAY_2(e);
}
static void ui_event_relay_3(lv_event_t * e) {
    if(lv_event_get_code(e) == LV_EVENT_VALUE_CHANGED) RELAY_3(e);
}
static void ui_onclick_hide_element(lv_event_t * e) {
    if(lv_event_get_code(e) == LV_EVENT_CLICKED) {
        _ui_flag_modify(e->target, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}
void switch_state(lv_obj_t * obj, bool state) {
  if (state) {
      lv_obj_add_state(obj, LV_STATE_CHECKED);
  } else {
      lv_obj_clear_state(obj, LV_STATE_CHECKED);
  }
}
static void ui_event_activateKeyboard(lv_event_t * e) {
    if (lv_event_get_code(e) == LV_EVENT_FOCUSED) {
        lv_keyboard_set_textarea(ui_Keyboard, lv_event_get_target(e));
    }
}

static void ui_style_textarea(lv_obj_t * obj) {
    lv_obj_add_event_cb(obj, ui_event_activateKeyboard, LV_EVENT_FOCUSED, NULL);
    lv_obj_set_style_text_font(obj, &ui_font_rubik_light_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x141414), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_textarea_set_one_line(obj, true);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_textarea_set_text(obj, "");
}

static void ui_style_switch(lv_obj_t * obj) {
    lv_obj_set_style_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x141414), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x00A099), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(obj, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);
}

static void ui_style_label(lv_obj_t * obj, char * text, int x, int y) {
    lv_label_set_text(obj, text);
    lv_obj_set_x(obj, x);
    lv_obj_set_y(obj, y);
    lv_obj_set_width(obj, LV_SIZE_CONTENT);
    lv_obj_set_height(obj, LV_SIZE_CONTENT);
    lv_obj_set_style_text_font(obj, &ui_font_rubik_light_18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
}

static void ui_style_position(lv_obj_t * obj, int x, int y, int height, int width, lv_align_t align) {
    lv_obj_set_x(obj, x);
    lv_obj_set_y(obj, y);
    lv_obj_set_height(obj, height);
    lv_obj_set_width(obj, width);
    lv_obj_set_align(obj, align);
}

static void ui_style_group(lv_obj_t * obj) {
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
}


static void ui_style_navbutton(lv_obj_t * obj, int x, void * cb, lv_obj_t * icon_obj, const void * icon) {
    lv_obj_set_height(obj, 77);
    lv_obj_set_width(obj, lv_pct(20));
    lv_obj_set_x(obj, x);
    lv_obj_set_y(obj, 0);
    
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);
    lv_obj_add_event_cb(obj, cb, LV_EVENT_ALL, NULL);
    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x141414), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0x00A099), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(obj, lv_color_hex(0x888888), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_img_set_src(icon_obj, icon);
    lv_obj_set_width(icon_obj, LV_SIZE_CONTENT);
    lv_obj_set_height(icon_obj, LV_SIZE_CONTENT);
    lv_obj_set_x(icon_obj, 0);
    lv_obj_set_y(icon_obj, 0);
    lv_obj_set_align(icon_obj, LV_ALIGN_CENTER);
    lv_obj_clear_flag(icon_obj, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

}


///////////////////// SCREENS ////////////////////
void ui_MainScreen_screen_init(void) {
    // ui_MainScreen
    ui_MainScreen = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_MainScreen, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM);

    lv_obj_add_event_cb(ui_MainScreen, ui_event_MainScreen, LV_EVENT_ALL, NULL);

    // ui_Content
    ui_Content = lv_obj_create(ui_MainScreen);

    lv_obj_set_height(ui_Content, 522);
    lv_obj_set_width(ui_Content, lv_pct(100));

    lv_obj_set_x(ui_Content, 0);
    lv_obj_set_y(ui_Content, 0);

    lv_obj_clear_flag(ui_Content, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_radius(ui_Content, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Content, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Content, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Content, &ui_img_bg_car_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Content, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Content, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Content, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Content, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Content, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_LevelInfo1
    ui_LevelInfo1 = lv_obj_create(ui_Content);

    lv_obj_set_width(ui_LevelInfo1, 280);
    lv_obj_set_height(ui_LevelInfo1, 205);

    lv_obj_set_x(ui_LevelInfo1, lv_pct(-25));
    lv_obj_set_y(ui_LevelInfo1, lv_pct(0));

    lv_obj_set_align(ui_LevelInfo1, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_LevelInfo1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_radius(ui_LevelInfo1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_LevelInfo1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_LevelInfo1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_LevelInfo1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_LevelInfo1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_LevelInfo1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Level1
    ui_Level1 = lv_bar_create(ui_LevelInfo1);
    lv_bar_set_range(ui_Level1, 0, 100);

    lv_obj_set_width(ui_Level1, 90);
    lv_obj_set_height(ui_Level1, 200);

    lv_obj_set_x(ui_Level1, 0);
    lv_obj_set_y(ui_Level1, 0);

    lv_obj_clear_flag(ui_Level1, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE);

    lv_obj_set_style_radius(ui_Level1, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Level1, lv_color_hex(0x141414), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Level1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_Level1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_Level1, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Level1, lv_color_hex(0x2DAB66), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Level1, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Level1, lv_color_hex(0x00A099), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Level1, LV_GRAD_DIR_VER, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // ui_Level1Mark25
    ui_Level1Mark25 = lv_obj_create(ui_Level1);

    lv_obj_set_height(ui_Level1Mark25, 1);
    lv_obj_set_width(ui_Level1Mark25, lv_pct(100));

    lv_obj_set_x(ui_Level1Mark25, 0);
    lv_obj_set_y(ui_Level1Mark25, lv_pct(75));

    lv_obj_clear_flag(ui_Level1Mark25, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    // ui_Level1Mark50
    ui_Level1Mark50 = lv_obj_create(ui_Level1);

    lv_obj_set_height(ui_Level1Mark50, 1);
    lv_obj_set_width(ui_Level1Mark50, lv_pct(100));

    lv_obj_set_x(ui_Level1Mark50, 0);
    lv_obj_set_y(ui_Level1Mark50, lv_pct(50));

    lv_obj_clear_flag(ui_Level1Mark50, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    // ui_Level1Mark75
    ui_Level1Mark75 = lv_obj_create(ui_Level1);

    lv_obj_set_height(ui_Level1Mark75, 1);
    lv_obj_set_width(ui_Level1Mark75, lv_pct(100));

    lv_obj_set_x(ui_Level1Mark75, 0);
    lv_obj_set_y(ui_Level1Mark75, lv_pct(25));

    lv_obj_clear_flag(ui_Level1Mark75, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    // ui_Level1Icon
    ui_Level1Icon = lv_img_create(ui_LevelInfo1);
    lv_img_set_src(ui_Level1Icon, &ui_img_icon_water_content_clean_png);

    lv_obj_set_width(ui_Level1Icon, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Level1Icon, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Level1Icon, 120);
    lv_obj_set_y(ui_Level1Icon, 0);

    lv_obj_clear_flag(ui_Level1Icon, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_opa(ui_Level1Icon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Level1State
    ui_Level1State = lv_label_create(ui_LevelInfo1);

    lv_obj_set_width(ui_Level1State, 160);
    lv_obj_set_height(ui_Level1State, 60);

    lv_obj_set_x(ui_Level1State, 120);
    lv_obj_set_y(ui_Level1State, 100);

    lv_label_set_text(ui_Level1State, "NA%");

    lv_obj_clear_flag(ui_Level1State, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_text_color(ui_Level1State, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Level1State, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Level1State, &ui_font_rubik_bold_53, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_Level1State, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Level1Label
    ui_Level1Label = lv_label_create(ui_LevelInfo1);

    lv_obj_set_width(ui_Level1Label, 160);
    lv_obj_set_height(ui_Level1Label, 30);

    lv_obj_set_x(ui_Level1Label, 120);
    lv_obj_set_y(ui_Level1Label, 170);

    lv_label_set_long_mode(ui_Level1Label, LV_LABEL_LONG_DOT);
    lv_label_set_text(ui_Level1Label, "FRESH WATER");

    lv_obj_clear_flag(ui_Level1Label, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_text_color(ui_Level1Label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Level1Label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Level1Label, &ui_font_rubik_SemiBold_22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_Level1Label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_LevelInfo2
    ui_LevelInfo2 = lv_obj_create(ui_Content);

    lv_obj_set_width(ui_LevelInfo2, 280);
    lv_obj_set_height(ui_LevelInfo2, 205);

    lv_obj_set_x(ui_LevelInfo2, lv_pct(5));
    lv_obj_set_y(ui_LevelInfo2, lv_pct(0));

    lv_obj_set_align(ui_LevelInfo2, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_LevelInfo2, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_radius(ui_LevelInfo2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_LevelInfo2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_LevelInfo2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_LevelInfo2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_LevelInfo2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_LevelInfo2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Level2
    ui_Level2 = lv_bar_create(ui_LevelInfo2);
    lv_bar_set_range(ui_Level2, 0, 100);

    lv_obj_set_width(ui_Level2, 90);
    lv_obj_set_height(ui_Level2, 200);

    lv_obj_set_x(ui_Level2, 0);
    lv_obj_set_y(ui_Level2, 0);

    lv_obj_clear_flag(ui_Level2, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE);

    lv_obj_set_style_radius(ui_Level2, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Level2, lv_color_hex(0x141414), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Level2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_Level2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_Level2, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Level2, lv_color_hex(0x2DAB66), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Level2, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Level2, lv_color_hex(0x00A099), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Level2, LV_GRAD_DIR_VER, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // ui_Level2Mark25
    ui_Level2Mark25 = lv_obj_create(ui_Level2);

    lv_obj_set_height(ui_Level2Mark25, 1);
    lv_obj_set_width(ui_Level2Mark25, lv_pct(100));

    lv_obj_set_x(ui_Level2Mark25, 0);
    lv_obj_set_y(ui_Level2Mark25, lv_pct(75));

    lv_obj_clear_flag(ui_Level2Mark25, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    // ui_Level2Mark50
    ui_Level2Mark50 = lv_obj_create(ui_Level2);

    lv_obj_set_height(ui_Level2Mark50, 1);
    lv_obj_set_width(ui_Level2Mark50, lv_pct(100));

    lv_obj_set_x(ui_Level2Mark50, 0);
    lv_obj_set_y(ui_Level2Mark50, lv_pct(50));

    lv_obj_clear_flag(ui_Level2Mark50, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    // ui_Level2Mark75
    ui_Level2Mark75 = lv_obj_create(ui_Level2);

    lv_obj_set_height(ui_Level2Mark75, 1);
    lv_obj_set_width(ui_Level2Mark75, lv_pct(100));

    lv_obj_set_x(ui_Level2Mark75, 0);
    lv_obj_set_y(ui_Level2Mark75, lv_pct(25));

    lv_obj_clear_flag(ui_Level2Mark75, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    // ui_Level2Icon
    ui_Level2Icon = lv_img_create(ui_LevelInfo2);
    lv_img_set_src(ui_Level2Icon, &ui_img_icon_water_content_dirty_png);

    lv_obj_set_width(ui_Level2Icon, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Level2Icon, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Level2Icon, 120);
    lv_obj_set_y(ui_Level2Icon, 0);

    lv_obj_clear_flag(ui_Level2Icon, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_opa(ui_Level2Icon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Level2State
    ui_Level2State = lv_label_create(ui_LevelInfo2);

    lv_obj_set_width(ui_Level2State, 160);
    lv_obj_set_height(ui_Level2State, 60);

    lv_obj_set_x(ui_Level2State, 120);
    lv_obj_set_y(ui_Level2State, 100);

    lv_label_set_text(ui_Level2State, "NA%");

    lv_obj_clear_flag(ui_Level2State, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_text_color(ui_Level2State, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Level2State, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Level2State, &ui_font_rubik_bold_53, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_Level2State, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Level2Label

    ui_Level2Label = lv_label_create(ui_LevelInfo2);

    lv_obj_set_width(ui_Level2Label, 160);
    lv_obj_set_height(ui_Level2Label, 30);

    lv_obj_set_x(ui_Level2Label, 120);
    lv_obj_set_y(ui_Level2Label, 170);

    lv_label_set_text(ui_Level2Label, "GREY WATER");

    lv_obj_clear_flag(ui_Level2Label, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_text_color(ui_Level2Label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Level2Label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Level2Label, &ui_font_rubik_SemiBold_22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_Level2Label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_DateIndicator
    ui_DateIndicator = lv_label_create(ui_Content);

    lv_obj_set_width(ui_DateIndicator, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_DateIndicator, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_DateIndicator, 0);
    lv_obj_set_y(ui_DateIndicator, 0);

    lv_label_set_text(ui_DateIndicator, "01.01.2022");

    lv_obj_clear_flag(ui_DateIndicator, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_text_color(ui_DateIndicator, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DateIndicator, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_DateIndicator, &ui_font_rubik_light_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_TimeIndicator
    ui_TimeIndicator = lv_label_create(ui_Content);

    lv_obj_set_width(ui_TimeIndicator, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TimeIndicator, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TimeIndicator, 0);
    lv_obj_set_y(ui_TimeIndicator, 0);

    lv_obj_set_align(ui_TimeIndicator, LV_ALIGN_TOP_MID);

    lv_label_set_text(ui_TimeIndicator, "00:00");

    lv_obj_clear_flag(ui_TimeIndicator, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_text_color(ui_TimeIndicator, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TimeIndicator, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TimeIndicator, &ui_font_rubik_light_40, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_ButtonSettingsOpen
    ui_ButtonSettingsOpen = lv_imgbtn_create(ui_Content);
    lv_imgbtn_set_src(ui_ButtonSettingsOpen, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_icon_settings_png, NULL);

    lv_obj_set_width(ui_ButtonSettingsOpen, 46);
    lv_obj_set_height(ui_ButtonSettingsOpen, 46);

    lv_obj_set_x(ui_ButtonSettingsOpen, 0);
    lv_obj_set_y(ui_ButtonSettingsOpen, 0);

    lv_obj_set_align(ui_ButtonSettingsOpen, LV_ALIGN_TOP_RIGHT);

    lv_obj_clear_flag(ui_ButtonSettingsOpen,
                      LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                      LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_add_event_cb(ui_ButtonSettingsOpen, ui_event_ButtonSettingsOpen, LV_EVENT_ALL, NULL);
    lv_obj_set_style_img_recolor(ui_ButtonSettingsOpen, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_ButtonSettingsOpen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Relays
    ui_Relays = lv_obj_create(ui_Content);
    lv_obj_set_width(ui_Relays, 160);
    lv_obj_set_height(ui_Relays, 120);
    lv_obj_set_x(ui_Relays, 0);
    lv_obj_set_y(ui_Relays, 150);
    lv_obj_set_align(ui_Relays, LV_ALIGN_TOP_RIGHT);
    lv_obj_clear_flag(ui_Relays, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);
    lv_obj_set_style_radius(ui_Relays, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_Relays, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Relays, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Relays, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Relays, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Relays, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Relay1 = lv_switch_create(ui_Relays);
    ui_style_position(ui_Relay1, 0, 0, 32, 64, LV_ALIGN_TOP_LEFT);
    ui_style_switch(ui_Relay1);
    lv_obj_add_event_cb(ui_Relay1, ui_event_relay_1, LV_EVENT_ALL, NULL);
    ui_Relay1Label = lv_label_create(ui_Relays);
    ui_style_label(ui_Relay1Label, "1. Relay", 70, 5);

    ui_Relay2 = lv_switch_create(ui_Relays);
    ui_style_position(ui_Relay2, 0, 40, 32, 64, LV_ALIGN_TOP_LEFT);
    ui_style_switch(ui_Relay2);
    lv_obj_add_event_cb(ui_Relay2, ui_event_relay_2, LV_EVENT_ALL, NULL);
    ui_Relay2Label = lv_label_create(ui_Relays);
    ui_style_label(ui_Relay2Label, "2. Relay", 70, 45);

    ui_Relay3 = lv_switch_create(ui_Relays);
    ui_style_position(ui_Relay3, 0, 80, 32, 64, LV_ALIGN_TOP_LEFT);
    ui_style_switch(ui_Relay3);
    lv_obj_add_event_cb(ui_Relay3, ui_event_relay_3, LV_EVENT_ALL, NULL);
    ui_Relay3Label = lv_label_create(ui_Relays);
    ui_style_label(ui_Relay3Label, "3. Relay", 70, 85);

    // ui_Navigation
    ui_Navigation = lv_obj_create(ui_MainScreen);

    lv_obj_set_height(ui_Navigation, 80);
    lv_obj_set_width(ui_Navigation, lv_pct(100));

    lv_obj_set_x(ui_Navigation, 0);
    lv_obj_set_y(ui_Navigation, 0);

    lv_obj_set_align(ui_Navigation, LV_ALIGN_BOTTOM_MID);

    lv_obj_clear_flag(ui_Navigation, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_scrollbar_mode(ui_Navigation, LV_SCROLLBAR_MODE_OFF);

    lv_obj_set_style_radius(ui_Navigation, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Navigation, lv_color_hex(0x141414), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Navigation, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Navigation, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Navigation, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Navigation, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Navigation, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

/*
    ui_NavButton1 = lv_btn_create(ui_Navigation);
    ui_NavIcon1 = lv_img_create(ui_NavButton1);
    ui_style_navbutton(ui_NavButton1, 0, ui_event_NavButton1, ui_NavIcon1, &ui_img_icon_weather_png);
*/
    ui_NavButton2 = lv_btn_create(ui_Navigation);
    ui_NavIcon2 = lv_img_create(ui_NavButton2);
    ui_style_navbutton(ui_NavButton2, lv_pct(20), ui_event_NavButton2, ui_NavIcon2, &ui_img_icon_water_png);

    ui_NavButton3 = lv_btn_create(ui_Navigation);
    ui_NavIcon3 = lv_img_create(ui_NavButton3);
    ui_style_navbutton(ui_NavButton3, lv_pct(40), ui_event_NavButton3, ui_NavIcon3, &ui_img_icon_battery_png);

    ui_NavButton4 = lv_btn_create(ui_Navigation);
    ui_NavIcon4 = lv_img_create(ui_NavButton4);
    ui_style_navbutton(ui_NavButton4, lv_pct(60), ui_event_NavButton4, ui_NavIcon4, &ui_img_icon_gas_png);

/*
    ui_NavButton5 = lv_btn_create(ui_Navigation);
    ui_NavIcon5 = lv_img_create(ui_NavButton5);
    ui_style_navbutton(ui_NavButton5, lv_pct(80), ui_event_NavButton5, ui_NavIcon5, &ui_img_icon_temperature_png);
*/
    // ui_WarnMessage
    ui_WarnMessage = lv_label_create(ui_MainScreen);
    lv_obj_set_width(ui_WarnMessage, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_WarnMessage, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_WarnMessage, 0);
    lv_obj_set_y(ui_WarnMessage, 75);
    lv_label_set_text(ui_WarnMessage, "An unknown error occurred");

    lv_obj_set_align(ui_WarnMessage, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_WarnMessage, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(ui_WarnMessage, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);
    lv_obj_add_event_cb(ui_WarnMessage, ui_onclick_hide_element, LV_EVENT_ALL, NULL);

    // Style a danger Warning
    lv_obj_set_style_text_color(ui_WarnMessage, lv_color_hex(0x842029), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_WarnMessage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_WarnMessage, &ui_font_rubik_SemiBold_22, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_WarnMessage, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_WarnMessage, lv_color_hex(0xF8D7DA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_WarnMessage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_WarnMessage, lv_color_hex(0xF5C2C7), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_WarnMessage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_WarnMessage, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_WarnMessage, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_WarnMessage, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_WarnMessage, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void ui_Settings_screen_init(void) {
    // ui_Settings
    ui_Settings = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Settings, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_event_cb(ui_Settings, ui_event_Settings, LV_EVENT_ALL, NULL);
    lv_obj_set_style_bg_img_src(ui_Settings, &ui_img_bg_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_ButtonSettingsClose
    ui_ButtonSettingsClose = lv_imgbtn_create(ui_Settings);
    lv_imgbtn_set_src(ui_ButtonSettingsClose, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_icon_close_png, NULL);
    lv_obj_set_width(ui_ButtonSettingsClose, 46);
    lv_obj_set_height(ui_ButtonSettingsClose, 46);
    lv_obj_set_x(ui_ButtonSettingsClose, -20);
    lv_obj_set_y(ui_ButtonSettingsClose, 20);
    lv_obj_set_align(ui_ButtonSettingsClose, LV_ALIGN_TOP_RIGHT);
    lv_obj_clear_flag(ui_ButtonSettingsClose,
                      LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                      LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_add_event_cb(ui_ButtonSettingsClose, ui_event_ButtonSettingsClose, LV_EVENT_ALL, NULL);

    // ui_Keyboard
    ui_Keyboard = lv_keyboard_create(ui_Settings);
    lv_obj_set_width(ui_Keyboard, lv_pct(100));
    lv_obj_set_height(ui_Keyboard, lv_pct(35));
    lv_obj_set_x(ui_Keyboard, 0);
    lv_obj_set_y(ui_Keyboard, 0);
    lv_obj_set_align(ui_Keyboard, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(ui_Keyboard, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

//// **** LEFT **** ////
    // ui_MqttConnection
    ui_MqttConnection = lv_obj_create(ui_Settings);
    ui_style_group(ui_MqttConnection);
    ui_style_position(ui_MqttConnection, 50, 50, 165, 302, LV_ALIGN_TOP_LEFT);
    ui_MqttServerLabel = lv_label_create(ui_MqttConnection);
    ui_style_label(ui_MqttServerLabel, "MQTT Server", 0, 0);
    ui_MqttHost = lv_textarea_create(ui_MqttConnection);
    ui_style_position(ui_MqttHost, 0, 25, 25, lv_pct(80), LV_ALIGN_TOP_RIGHT);
    ui_style_textarea(ui_MqttHost);
    lv_textarea_set_placeholder_text(ui_MqttHost, "IP or Hostname");
    ui_MqttPort = lv_textarea_create(ui_MqttConnection);
    ui_style_position(ui_MqttPort, 0, 60, 25, lv_pct(80), LV_ALIGN_TOP_RIGHT);
    ui_style_textarea(ui_MqttPort);
    lv_textarea_set_placeholder_text(ui_MqttPort, "Port");
    lv_textarea_set_accepted_chars(ui_MqttPort, "0123456789");
    lv_textarea_set_max_length(ui_MqttPort, 5);
    ui_MqttUsername = lv_textarea_create(ui_MqttConnection);
    ui_style_position(ui_MqttUsername, 0, 95, 25, lv_pct(80), LV_ALIGN_TOP_RIGHT);
    ui_style_textarea(ui_MqttUsername);
    lv_textarea_set_placeholder_text(ui_MqttUsername, "Username");
    ui_MqttPassword = lv_textarea_create(ui_MqttConnection);
    ui_style_position(ui_MqttPassword, 0, 130, 25, lv_pct(80), LV_ALIGN_TOP_RIGHT);
    ui_style_textarea(ui_MqttPassword);
    lv_textarea_set_placeholder_text(ui_MqttPassword, "Password");

    // ui_FreshWaterLevel
    ui_FreshWaterLevel = lv_obj_create(ui_Settings);
    ui_style_group(ui_FreshWaterLevel);
    ui_style_position(ui_FreshWaterLevel, 50, 230, 50, 302, LV_ALIGN_TOP_LEFT);
    ui_EnableFreshWater = lv_switch_create(ui_FreshWaterLevel);
    ui_style_position(ui_EnableFreshWater, 0, 0, 25, 50, LV_ALIGN_BOTTOM_LEFT);
    ui_style_switch(ui_EnableFreshWater);
    ui_FreshWaterLabel = lv_label_create(ui_FreshWaterLevel);
    ui_style_label(ui_FreshWaterLabel, "Fresh water sensor", 0, 0);
    ui_FreshWaterTopic = lv_textarea_create(ui_FreshWaterLevel);
    ui_style_position(ui_FreshWaterTopic, 0, 0, 25, lv_pct(80), LV_ALIGN_BOTTOM_RIGHT);
    ui_style_textarea(ui_FreshWaterTopic);
    lv_textarea_set_placeholder_text(ui_FreshWaterTopic, "identifier / mqtt topic");

    // ui_GreyWaterLevel
    ui_GreyWaterLevel = lv_obj_create(ui_Settings);
    ui_style_group(ui_GreyWaterLevel);
    ui_style_position(ui_GreyWaterLevel, 50, 290, 50, 302, LV_ALIGN_TOP_LEFT);
    ui_EnableGreyWater = lv_switch_create(ui_GreyWaterLevel);
    ui_style_position(ui_EnableGreyWater, 0, 0, 25, 50, LV_ALIGN_BOTTOM_LEFT);
    ui_style_switch(ui_EnableGreyWater);
    ui_GreyWaterLabel = lv_label_create(ui_GreyWaterLevel);
    ui_style_label(ui_GreyWaterLabel, "Grey water sensor", 0, 0);
    ui_GreyWaterTopic = lv_textarea_create(ui_GreyWaterLevel);
    ui_style_position(ui_GreyWaterTopic, 0, 0, 25, lv_pct(80), LV_ALIGN_BOTTOM_RIGHT);
    ui_style_textarea(ui_GreyWaterTopic);
    lv_textarea_set_placeholder_text(ui_GreyWaterTopic, "identifier / mqtt topic");

//// **** MIDDLE **** ////
    // ui_Gaslevel
    ui_GasSensors = lv_obj_create(ui_Settings);
    ui_style_group(ui_GasSensors);
    ui_style_position(ui_GasSensors, 380, 50, 90, 302, LV_ALIGN_TOP_LEFT);
    ui_GasLabel1 = lv_label_create(ui_GasSensors);
    ui_style_label(ui_GasLabel1, "Gas bottle level", 0, 0);
    ui_EnableGas1 = lv_switch_create(ui_GasSensors);
    ui_style_position(ui_EnableGas1, 0, 25, 25, 50, LV_ALIGN_TOP_LEFT);
    ui_style_switch(ui_EnableGas1);
    ui_EnableGas2 = lv_switch_create(ui_GasSensors);
    ui_style_position(ui_EnableGas2, 0, 60, 25, 50, LV_ALIGN_TOP_LEFT);
    ui_style_switch(ui_EnableGas2);
    ui_GasTopic1 = lv_textarea_create(ui_GasSensors);
    ui_style_position(ui_GasTopic1, 0, 25, 25, lv_pct(80), LV_ALIGN_TOP_RIGHT);
    ui_style_textarea(ui_GasTopic1);
    lv_textarea_set_placeholder_text(ui_GasTopic1, "identifier / mqtt topic");
    ui_GasTopic2 = lv_textarea_create(ui_GasSensors);
    ui_style_position(ui_GasTopic2, 0, 60, 25, lv_pct(80), LV_ALIGN_TOP_RIGHT);
    ui_style_textarea(ui_GasTopic2);
    lv_textarea_set_placeholder_text(ui_GasTopic2, "identifier / mqtt topic");

    // ui_Batterylevel
    ui_BatterySensors = lv_obj_create(ui_Settings);
    ui_style_group(ui_BatterySensors);
    ui_style_position(ui_BatterySensors, 380, 150, 90, 302, LV_ALIGN_TOP_LEFT);
    ui_BatteryLabel1 = lv_label_create(ui_BatterySensors);
    ui_style_label(ui_BatteryLabel1, "Battery state of charge", 0, 0);
    ui_EnableBattery1 = lv_switch_create(ui_BatterySensors);
    ui_style_position(ui_EnableBattery1, 0, 25, 25, 50, LV_ALIGN_TOP_LEFT);
    ui_style_switch(ui_EnableBattery1);
    ui_EnableBattery2 = lv_switch_create(ui_BatterySensors);
    ui_style_position(ui_EnableBattery2, 0, 60, 25, 50, LV_ALIGN_TOP_LEFT);
    ui_style_switch(ui_EnableBattery2);
    ui_BatteryTopic1 = lv_textarea_create(ui_BatterySensors);
    ui_style_position(ui_BatteryTopic1, 0, 25, 25, lv_pct(80), LV_ALIGN_TOP_RIGHT);
    ui_style_textarea(ui_BatteryTopic1);
    lv_textarea_set_placeholder_text(ui_BatteryTopic1, "identifier / mqtt topic");
    ui_BatteryTopic2 = lv_textarea_create(ui_BatterySensors);
    ui_style_position(ui_BatteryTopic2, 0, 60, 25, lv_pct(80), LV_ALIGN_TOP_RIGHT);
    ui_style_textarea(ui_BatteryTopic2);
    lv_textarea_set_placeholder_text(ui_BatteryTopic2, "identifier / mqtt topic");

    // ui_Display
    ui_Display = lv_obj_create(ui_Settings);
    ui_style_group(ui_Display);
    ui_style_position(ui_Display, 380, 250, 130, 302, LV_ALIGN_TOP_LEFT);
    ui_DisplayDimEnable = lv_switch_create(ui_Display);
    ui_style_position(ui_DisplayDimEnable, 0, 25, 25, 50, LV_ALIGN_TOP_LEFT);
    ui_style_switch(ui_DisplayDimEnable);
    ui_DisplayLabel = lv_label_create(ui_Display);
    ui_style_label(ui_DisplayLabel, "Display Backlight Dimming", 0, 0);
    ui_DisplayDimTimeout = lv_textarea_create(ui_Display);
    ui_style_position(ui_DisplayDimTimeout, 0, 25, 25, lv_pct(80), LV_ALIGN_TOP_RIGHT);
    ui_style_textarea(ui_DisplayDimTimeout);
    lv_textarea_set_placeholder_text(ui_DisplayDimTimeout, "timeout in sec");
    ui_DisplayBacklightMax = lv_textarea_create(ui_Display);
    ui_style_position(ui_DisplayBacklightMax, 0, 60, 25, lv_pct(80), LV_ALIGN_TOP_RIGHT);
    ui_style_textarea(ui_DisplayBacklightMax);
    lv_textarea_set_placeholder_text(ui_DisplayBacklightMax, "typical 1 (max light)");
    ui_DisplayBacklightMin = lv_textarea_create(ui_Display);
    ui_style_position(ui_DisplayBacklightMin, 0, 95, 25, lv_pct(80), LV_ALIGN_TOP_RIGHT);
    ui_style_textarea(ui_DisplayBacklightMin);
    lv_textarea_set_placeholder_text(ui_DisplayBacklightMin, "typical 255 (no light)");

//// **** RIGHT **** ////
    // ui_relays
    ui_RelaysSettings = lv_obj_create(ui_Settings);
    ui_style_group(ui_RelaysSettings);
    ui_style_position(ui_RelaysSettings, 710, 50, 90, 302, LV_ALIGN_TOP_LEFT);
    ui_RelaysLabel = lv_label_create(ui_RelaysSettings);
    ui_style_label(ui_RelaysLabel, "Relay GPIOs", 0, 0);

    ui_Relay1GPIO = lv_textarea_create(ui_RelaysSettings);
    ui_style_position(ui_Relay1GPIO, 0, 25, 25, lv_pct(33), LV_ALIGN_TOP_LEFT);
    ui_style_textarea(ui_Relay1GPIO);
    lv_textarea_set_placeholder_text(ui_Relay1GPIO, "Relay 1");
    ui_Relay2GPIO = lv_textarea_create(ui_RelaysSettings);
    ui_style_position(ui_Relay2GPIO, lv_pct(33), 25, 25, lv_pct(33), LV_ALIGN_TOP_LEFT);
    ui_style_textarea(ui_Relay2GPIO);
    lv_textarea_set_placeholder_text(ui_Relay2GPIO, "Relay 2");
    ui_Relay3GPIO = lv_textarea_create(ui_RelaysSettings);
    ui_style_position(ui_Relay3GPIO, lv_pct(66), 25, 25, lv_pct(33), LV_ALIGN_TOP_LEFT);
    ui_style_textarea(ui_Relay3GPIO);
    lv_textarea_set_placeholder_text(ui_Relay3GPIO, "Relay 3");

    // Activate the keyboard in the first input field
    lv_keyboard_set_textarea(ui_Keyboard, ui_MqttHost);
}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_MainScreen_screen_init();
    ui_Settings_screen_init();
    lv_disp_load_scr(ui_MainScreen);
}

