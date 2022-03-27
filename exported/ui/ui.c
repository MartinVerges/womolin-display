// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.4
// LVGL VERSION: 8.2
// PROJECT: hud

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_MainScreen;
lv_obj_t * ui_Navigation;
lv_obj_t * ui_NavButton1;
lv_obj_t * ui_NavIcon1;
lv_obj_t * ui_NavButton2;
lv_obj_t * ui_NavIcon2;
lv_obj_t * ui_NavButton3;
lv_obj_t * ui_NavIcon3;
lv_obj_t * ui_NavButton4;
lv_obj_t * ui_NavIcon4;
lv_obj_t * ui_Content;
lv_obj_t * ui_Level;
lv_obj_t * ui_LevelMark25;
lv_obj_t * ui_LevelMark50;
lv_obj_t * ui_LevelMark75;
lv_obj_t * ui_LevelIcon;
lv_obj_t * ui_LevelState;
lv_obj_t * ui_LevelLabel;
lv_obj_t * ui_DateIndicator;
lv_obj_t * ui_TimeIndicator;
lv_obj_t * ui_SettingsButton;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 32
    #error "LV_COLOR_DEPTH should be 32bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "#error LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
static void ui_event_NavButton1(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        ONCLICK_NAV_1(e);
    }
}
static void ui_event_NavButton2(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        ONCLICK_NAV_2(e);
    }
}
static void ui_event_NavButton3(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        ONCLICK_NAV_3(e);
    }
}
static void ui_event_NavButton4(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        ONCLICK_NAV_4(e);
    }
}
static void ui_event_SettingsButton(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        ONCLICK_SETTINGS(e);
    }
}

///////////////////// SCREENS ////////////////////
void ui_MainScreen_screen_init(void)
{

    // ui_MainScreen

    ui_MainScreen = lv_obj_create(NULL);

    lv_obj_clear_flag(ui_MainScreen, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM);

    lv_obj_set_style_bg_img_src(ui_MainScreen, &ui_img_bg_car_png, LV_PART_MAIN | LV_STATE_DEFAULT);

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
    lv_obj_set_style_opa(ui_Navigation, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Navigation, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Navigation, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Navigation, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Navigation, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_NavButton1

    ui_NavButton1 = lv_btn_create(ui_Navigation);

    lv_obj_set_width(ui_NavButton1, 254);
    lv_obj_set_height(ui_NavButton1, 77);

    lv_obj_set_x(ui_NavButton1, 0);
    lv_obj_set_y(ui_NavButton1, 0);

    lv_obj_clear_flag(ui_NavButton1, LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_add_event_cb(ui_NavButton1, ui_event_NavButton1, LV_EVENT_ALL, NULL);
    lv_obj_set_style_radius(ui_NavButton1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_NavButton1, lv_color_hex(0x2DAB66), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_NavButton1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_NavButton1, lv_color_hex(0x00A099), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_NavButton1, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_NavButton1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_NavIcon1

    ui_NavIcon1 = lv_img_create(ui_NavButton1);
    lv_img_set_src(ui_NavIcon1, &ui_img_icon_weather_active_png);

    lv_obj_set_width(ui_NavIcon1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_NavIcon1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_NavIcon1, 0);
    lv_obj_set_y(ui_NavIcon1, 0);

    lv_obj_set_align(ui_NavIcon1, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_NavIcon1, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_clear_flag(ui_NavIcon1, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    // ui_NavButton2

    ui_NavButton2 = lv_btn_create(ui_Navigation);

    lv_obj_set_width(ui_NavButton2, 254);
    lv_obj_set_height(ui_NavButton2, 77);

    lv_obj_set_x(ui_NavButton2, 257);
    lv_obj_set_y(ui_NavButton2, 0);

    lv_obj_clear_flag(ui_NavButton2, LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_add_event_cb(ui_NavButton2, ui_event_NavButton2, LV_EVENT_ALL, NULL);
    lv_obj_set_style_radius(ui_NavButton2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_NavButton2, lv_color_hex(0x141414), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_NavButton2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_NavButton2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_NavIcon2

    ui_NavIcon2 = lv_img_create(ui_NavButton2);
    lv_img_set_src(ui_NavIcon2, &ui_img_icon_water_inactive_png);

    lv_obj_set_width(ui_NavIcon2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_NavIcon2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_NavIcon2, 0);
    lv_obj_set_y(ui_NavIcon2, 0);

    lv_obj_set_align(ui_NavIcon2, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_NavIcon2, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_clear_flag(ui_NavIcon2, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    // ui_NavButton3

    ui_NavButton3 = lv_btn_create(ui_Navigation);

    lv_obj_set_width(ui_NavButton3, 254);
    lv_obj_set_height(ui_NavButton3, 77);

    lv_obj_set_x(ui_NavButton3, 514);
    lv_obj_set_y(ui_NavButton3, 0);

    lv_obj_clear_flag(ui_NavButton3, LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_add_event_cb(ui_NavButton3, ui_event_NavButton3, LV_EVENT_ALL, NULL);
    lv_obj_set_style_radius(ui_NavButton3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_NavButton3, lv_color_hex(0x141414), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_NavButton3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_NavButton3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_NavIcon3

    ui_NavIcon3 = lv_img_create(ui_NavButton3);
    lv_img_set_src(ui_NavIcon3, &ui_img_icon_gas_inactive_png);

    lv_obj_set_width(ui_NavIcon3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_NavIcon3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_NavIcon3, 0);
    lv_obj_set_y(ui_NavIcon3, 0);

    lv_obj_set_align(ui_NavIcon3, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_NavIcon3, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_clear_flag(ui_NavIcon3, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    // ui_NavButton4

    ui_NavButton4 = lv_btn_create(ui_Navigation);

    lv_obj_set_width(ui_NavButton4, 254);
    lv_obj_set_height(ui_NavButton4, 77);

    lv_obj_set_x(ui_NavButton4, 771);
    lv_obj_set_y(ui_NavButton4, 0);

    lv_obj_clear_flag(ui_NavButton4, LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_add_event_cb(ui_NavButton4, ui_event_NavButton4, LV_EVENT_ALL, NULL);
    lv_obj_set_style_radius(ui_NavButton4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_NavButton4, lv_color_hex(0x141414), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_NavButton4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_NavButton4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_NavIcon4

    ui_NavIcon4 = lv_img_create(ui_NavButton4);
    lv_img_set_src(ui_NavIcon4, &ui_img_icon_battery_inactive_png);

    lv_obj_set_width(ui_NavIcon4, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_NavIcon4, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_NavIcon4, 0);
    lv_obj_set_y(ui_NavIcon4, 0);

    lv_obj_set_align(ui_NavIcon4, LV_ALIGN_CENTER);

    lv_obj_add_flag(ui_NavIcon4, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_clear_flag(ui_NavIcon4, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    // ui_Content

    ui_Content = lv_obj_create(ui_MainScreen);

    lv_obj_set_width(ui_Content, lv_pct(90));
    lv_obj_set_height(ui_Content, lv_pct(70));

    lv_obj_set_x(ui_Content, 0);
    lv_obj_set_y(ui_Content, 0);

    lv_obj_set_align(ui_Content, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_Content, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_radius(ui_Content, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Content, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Content, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Content, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Level

    ui_Level = lv_bar_create(ui_Content);
    lv_bar_set_range(ui_Level, 0, 100);
    lv_bar_set_value(ui_Level, 85, LV_ANIM_OFF);

    lv_obj_set_width(ui_Level, 90);
    lv_obj_set_height(ui_Level, 174);

    lv_obj_set_x(ui_Level, 100);
    lv_obj_set_y(ui_Level, 70);

    lv_obj_clear_flag(ui_Level, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE);

    lv_obj_set_style_radius(ui_Level, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Level, lv_color_hex(0x141414), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Level, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_Level, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Level, lv_color_hex(0x2DAB66), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Level, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_Level, lv_color_hex(0x00A099), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_Level, LV_GRAD_DIR_VER, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    // ui_LevelMark25

    ui_LevelMark25 = lv_obj_create(ui_Level);

    lv_obj_set_height(ui_LevelMark25, 1);
    lv_obj_set_width(ui_LevelMark25, lv_pct(100));

    lv_obj_set_x(ui_LevelMark25, 0);
    lv_obj_set_y(ui_LevelMark25, lv_pct(75));

    lv_obj_clear_flag(ui_LevelMark25, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    // ui_LevelMark50

    ui_LevelMark50 = lv_obj_create(ui_Level);

    lv_obj_set_height(ui_LevelMark50, 1);
    lv_obj_set_width(ui_LevelMark50, lv_pct(100));

    lv_obj_set_x(ui_LevelMark50, 0);
    lv_obj_set_y(ui_LevelMark50, lv_pct(50));

    lv_obj_clear_flag(ui_LevelMark50, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    // ui_LevelMark75

    ui_LevelMark75 = lv_obj_create(ui_Level);

    lv_obj_set_height(ui_LevelMark75, 1);
    lv_obj_set_width(ui_LevelMark75, lv_pct(100));

    lv_obj_set_x(ui_LevelMark75, 0);
    lv_obj_set_y(ui_LevelMark75, lv_pct(25));

    lv_obj_clear_flag(ui_LevelMark75, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
                      LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
                      LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    // ui_LevelIcon

    ui_LevelIcon = lv_img_create(ui_Content);
    lv_img_set_src(ui_LevelIcon, &ui_img_icon_water_content_png);

    lv_obj_set_width(ui_LevelIcon, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LevelIcon, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LevelIcon, 220);
    lv_obj_set_y(ui_LevelIcon, 70);

    lv_obj_clear_flag(ui_LevelIcon, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    // ui_LevelState

    ui_LevelState = lv_label_create(ui_Content);

    lv_obj_set_width(ui_LevelState, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LevelState, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LevelState, 220);
    lv_obj_set_y(ui_LevelState, 160);

    lv_label_set_text(ui_LevelState, "85%");

    lv_obj_clear_flag(ui_LevelState, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_text_color(ui_LevelState, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LevelState, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LevelState, &ui_font_rubik_bold_53, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_LevelLabel

    ui_LevelLabel = lv_label_create(ui_Content);

    lv_obj_set_width(ui_LevelLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_LevelLabel, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_LevelLabel, 220);
    lv_obj_set_y(ui_LevelLabel, 220);

    lv_label_set_text(ui_LevelLabel, "FRESH WATER");

    lv_obj_clear_flag(ui_LevelLabel, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_text_color(ui_LevelLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LevelLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LevelLabel, &ui_font_rubik_SemiBold_22, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_DateIndicator

    ui_DateIndicator = lv_label_create(ui_MainScreen);

    lv_obj_set_width(ui_DateIndicator, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_DateIndicator, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_DateIndicator, 29);
    lv_obj_set_y(ui_DateIndicator, 25);

    lv_label_set_text(ui_DateIndicator, "Sunday 27.03.2022");

    lv_obj_clear_flag(ui_DateIndicator, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_text_color(ui_DateIndicator, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_DateIndicator, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_DateIndicator, &ui_font_rubik_light_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_TimeIndicator

    ui_TimeIndicator = lv_label_create(ui_MainScreen);

    lv_obj_set_width(ui_TimeIndicator, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_TimeIndicator, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_TimeIndicator, 0);
    lv_obj_set_y(ui_TimeIndicator, 13);

    lv_obj_set_align(ui_TimeIndicator, LV_ALIGN_TOP_MID);

    lv_label_set_text(ui_TimeIndicator, "12:34");

    lv_obj_clear_flag(ui_TimeIndicator, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_set_style_text_color(ui_TimeIndicator, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TimeIndicator, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TimeIndicator, &ui_font_rubik_light_40, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_SettingsButton

    ui_SettingsButton = lv_imgbtn_create(ui_MainScreen);
    lv_imgbtn_set_src(ui_SettingsButton, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_icon_settings_png, NULL);

    lv_obj_set_width(ui_SettingsButton, 46);
    lv_obj_set_height(ui_SettingsButton, 46);

    lv_obj_set_x(ui_SettingsButton, -29);
    lv_obj_set_y(ui_SettingsButton, 17);

    lv_obj_set_align(ui_SettingsButton, LV_ALIGN_TOP_RIGHT);

    lv_obj_clear_flag(ui_SettingsButton,
                      LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                      LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_add_event_cb(ui_SettingsButton, ui_event_SettingsButton, LV_EVENT_ALL, NULL);

}

void ui_init(void)
{
    ui_MainScreen_screen_init();
    lv_disp_load_scr(ui_MainScreen);
}

