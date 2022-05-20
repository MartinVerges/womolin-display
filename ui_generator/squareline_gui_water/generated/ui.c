// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.0.5
// LVGL VERSION: 8.2
// PROJECT: hud

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
lv_obj_t * ui_NavButton1;
lv_obj_t * ui_NavIcon1;
lv_obj_t * ui_NavButton2;
lv_obj_t * ui_NavIcon2;
lv_obj_t * ui_NavButton3;
lv_obj_t * ui_NavIcon3;
lv_obj_t * ui_NavButton4;
lv_obj_t * ui_NavIcon4;
lv_obj_t * ui_NavButton5;
lv_obj_t * ui_NavIcon5;
lv_obj_t * ui_Relays;
lv_obj_t * ui_Relay1;
lv_obj_t * ui_Relay1Label;
lv_obj_t * ui_Relay2;
lv_obj_t * ui_Relay2Label;
lv_obj_t * ui_Relay3;
lv_obj_t * ui_Relay3Label;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 32
    #error "LV_COLOR_DEPTH should be 32bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "#error LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
static void ui_event_MainScreen(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_SCREEN_LOADED) {
        LOADSCREEN(e);
    }
}
static void ui_event_ButtonSettingsOpen(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
}
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
static void ui_event_NavButton5(lv_event_t * e)
{
    lv_event_code_t event = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);
    if(event == LV_EVENT_CLICKED) {
        ONCLICK_NAV_5(e);
    }
}

///////////////////// SCREENS ////////////////////
void ui_MainScreen_screen_init(void)
{

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

    lv_label_set_text(ui_Level2Label, "GRAY WATER");

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

    lv_label_set_text(ui_DateIndicator, "Noday 01.01.2022");

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

    // ui_NavButton1

    ui_NavButton1 = lv_btn_create(ui_Navigation);

    lv_obj_set_height(ui_NavButton1, 77);
    lv_obj_set_width(ui_NavButton1, lv_pct(20));

    lv_obj_set_x(ui_NavButton1, 0);
    lv_obj_set_y(ui_NavButton1, 0);

    lv_obj_clear_flag(ui_NavButton1, LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_add_event_cb(ui_NavButton1, ui_event_NavButton1, LV_EVENT_ALL, NULL);
    lv_obj_set_style_radius(ui_NavButton1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_NavButton1, lv_color_hex(0x141414), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_NavButton1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_NavButton1, lv_color_hex(0x00A099), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_NavButton1, lv_color_hex(0x888888), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_NavButton1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_NavButton1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_NavButton1, LV_BORDER_SIDE_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_NavButton1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_NavIcon1

    ui_NavIcon1 = lv_img_create(ui_NavButton1);
    lv_img_set_src(ui_NavIcon1, &ui_img_icon_weather_png);

    lv_obj_set_width(ui_NavIcon1, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_NavIcon1, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_NavIcon1, 0);
    lv_obj_set_y(ui_NavIcon1, 0);

    lv_obj_set_align(ui_NavIcon1, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_NavIcon1, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    // ui_NavButton2

    ui_NavButton2 = lv_btn_create(ui_Navigation);

    lv_obj_set_height(ui_NavButton2, 77);
    lv_obj_set_width(ui_NavButton2, lv_pct(20));

    lv_obj_set_y(ui_NavButton2, 0);
    lv_obj_set_x(ui_NavButton2, lv_pct(20));

    lv_obj_clear_flag(ui_NavButton2, LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_add_event_cb(ui_NavButton2, ui_event_NavButton2, LV_EVENT_ALL, NULL);
    lv_obj_set_style_radius(ui_NavButton2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_NavButton2, lv_color_hex(0x141414), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_NavButton2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_NavButton2, lv_color_hex(0x00A099), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_NavButton2, lv_color_hex(0x888888), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_NavButton2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_NavButton2, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_NavButton2, LV_BORDER_SIDE_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_NavButton2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_NavIcon2

    ui_NavIcon2 = lv_img_create(ui_NavButton2);
    lv_img_set_src(ui_NavIcon2, &ui_img_icon_water_png);

    lv_obj_set_width(ui_NavIcon2, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_NavIcon2, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_NavIcon2, 0);
    lv_obj_set_y(ui_NavIcon2, 0);

    lv_obj_set_align(ui_NavIcon2, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_NavIcon2, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    // ui_NavButton3

    ui_NavButton3 = lv_btn_create(ui_Navigation);

    lv_obj_set_height(ui_NavButton3, 77);
    lv_obj_set_width(ui_NavButton3, lv_pct(20));

    lv_obj_set_y(ui_NavButton3, 0);
    lv_obj_set_x(ui_NavButton3, lv_pct(40));

    lv_obj_clear_flag(ui_NavButton3, LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_add_event_cb(ui_NavButton3, ui_event_NavButton3, LV_EVENT_ALL, NULL);
    lv_obj_set_style_radius(ui_NavButton3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_NavButton3, lv_color_hex(0x141414), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_NavButton3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_NavButton3, lv_color_hex(0x00A099), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_NavButton3, lv_color_hex(0x888888), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_NavButton3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_NavButton3, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_NavButton3, LV_BORDER_SIDE_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_NavButton3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_NavIcon3

    ui_NavIcon3 = lv_img_create(ui_NavButton3);
    lv_img_set_src(ui_NavIcon3, &ui_img_icon_battery_png);

    lv_obj_set_width(ui_NavIcon3, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_NavIcon3, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_NavIcon3, 0);
    lv_obj_set_y(ui_NavIcon3, 0);

    lv_obj_set_align(ui_NavIcon3, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_NavIcon3, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    // ui_NavButton4

    ui_NavButton4 = lv_btn_create(ui_Navigation);

    lv_obj_set_height(ui_NavButton4, 77);
    lv_obj_set_width(ui_NavButton4, lv_pct(20));

    lv_obj_set_y(ui_NavButton4, 0);
    lv_obj_set_x(ui_NavButton4, lv_pct(60));

    lv_obj_clear_flag(ui_NavButton4, LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_add_event_cb(ui_NavButton4, ui_event_NavButton4, LV_EVENT_ALL, NULL);
    lv_obj_set_style_radius(ui_NavButton4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_NavButton4, lv_color_hex(0x141414), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_NavButton4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_NavButton4, lv_color_hex(0x00A099), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_NavButton4, lv_color_hex(0x888888), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_NavButton4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_NavButton4, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_NavButton4, LV_BORDER_SIDE_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_NavButton4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_NavIcon4

    ui_NavIcon4 = lv_img_create(ui_NavButton4);
    lv_img_set_src(ui_NavIcon4, &ui_img_icon_gas_png);

    lv_obj_set_width(ui_NavIcon4, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_NavIcon4, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_NavIcon4, 0);
    lv_obj_set_y(ui_NavIcon4, 0);

    lv_obj_set_align(ui_NavIcon4, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_NavIcon4, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    // ui_NavButton5

    ui_NavButton5 = lv_btn_create(ui_Navigation);

    lv_obj_set_height(ui_NavButton5, 77);
    lv_obj_set_width(ui_NavButton5, lv_pct(20));

    lv_obj_set_y(ui_NavButton5, 0);
    lv_obj_set_x(ui_NavButton5, lv_pct(80));

    lv_obj_clear_flag(ui_NavButton5, LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);

    lv_obj_add_event_cb(ui_NavButton5, ui_event_NavButton5, LV_EVENT_ALL, NULL);
    lv_obj_set_style_radius(ui_NavButton5, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_NavButton5, lv_color_hex(0x141414), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_NavButton5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_NavButton5, lv_color_hex(0x00A099), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_NavButton5, lv_color_hex(0x888888), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_NavButton5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_NavButton5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_NavIcon5

    ui_NavIcon5 = lv_img_create(ui_NavButton5);
    lv_img_set_src(ui_NavIcon5, &ui_img_icon_temperature_png);

    lv_obj_set_width(ui_NavIcon5, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_NavIcon5, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_NavIcon5, 0);
    lv_obj_set_y(ui_NavIcon5, 0);

    lv_obj_set_align(ui_NavIcon5, LV_ALIGN_CENTER);

    lv_obj_clear_flag(ui_NavIcon5, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);

    // ui_Relays

    ui_Relays = lv_obj_create(ui_MainScreen);

    lv_obj_set_width(ui_Relays, 160);
    lv_obj_set_height(ui_Relays, 120);

    lv_obj_set_x(ui_Relays, 0);
    lv_obj_set_y(ui_Relays, 150);

    lv_obj_set_align(ui_Relays, LV_ALIGN_TOP_RIGHT);

    lv_obj_clear_flag(ui_Relays, LV_OBJ_FLAG_SCROLLABLE);

    // ui_Relay1

    ui_Relay1 = lv_switch_create(ui_Relays);

    lv_obj_set_width(ui_Relay1, 50);
    lv_obj_set_height(ui_Relay1, 25);

    lv_obj_set_x(ui_Relay1, 0);
    lv_obj_set_y(ui_Relay1, 0);

    lv_obj_set_style_opa(ui_Relay1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_Relay1, lv_color_hex(0x141414), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Relay1, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Relay1, lv_color_hex(0x00A099), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_Relay1, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    // ui_Relay1Label

    ui_Relay1Label = lv_label_create(ui_Relays);

    lv_obj_set_width(ui_Relay1Label, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Relay1Label, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Relay1Label, 0);
    lv_obj_set_y(ui_Relay1Label, 0);

    lv_obj_set_align(ui_Relay1Label, LV_ALIGN_TOP_RIGHT);

    lv_label_set_text(ui_Relay1Label, "1. Relay");

    lv_obj_set_style_text_font(ui_Relay1Label, &ui_font_rubik_light_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Relay2

    ui_Relay2 = lv_switch_create(ui_Relays);

    lv_obj_set_width(ui_Relay2, 50);
    lv_obj_set_height(ui_Relay2, 25);

    lv_obj_set_x(ui_Relay2, 0);
    lv_obj_set_y(ui_Relay2, 40);

    lv_obj_set_style_opa(ui_Relay2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_Relay2, lv_color_hex(0x141414), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Relay2, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Relay2, lv_color_hex(0x00A099), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_Relay2, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    // ui_Relay2Label

    ui_Relay2Label = lv_label_create(ui_Relays);

    lv_obj_set_width(ui_Relay2Label, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Relay2Label, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Relay2Label, 0);
    lv_obj_set_y(ui_Relay2Label, 40);

    lv_obj_set_align(ui_Relay2Label, LV_ALIGN_TOP_RIGHT);

    lv_label_set_text(ui_Relay2Label, "2. Relay");

    lv_obj_set_style_text_font(ui_Relay2Label, &ui_font_rubik_light_18, LV_PART_MAIN | LV_STATE_DEFAULT);

    // ui_Relay3

    ui_Relay3 = lv_switch_create(ui_Relays);

    lv_obj_set_width(ui_Relay3, 50);
    lv_obj_set_height(ui_Relay3, 25);

    lv_obj_set_x(ui_Relay3, 0);
    lv_obj_set_y(ui_Relay3, 80);

    lv_obj_set_style_opa(ui_Relay3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_Relay3, lv_color_hex(0x141414), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Relay3, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Relay3, lv_color_hex(0x00A099), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_Relay3, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    // ui_Relay3Label

    ui_Relay3Label = lv_label_create(ui_Relays);

    lv_obj_set_width(ui_Relay3Label, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_Relay3Label, LV_SIZE_CONTENT);

    lv_obj_set_x(ui_Relay3Label, 0);
    lv_obj_set_y(ui_Relay3Label, 80);

    lv_obj_set_align(ui_Relay3Label, LV_ALIGN_TOP_RIGHT);

    lv_label_set_text(ui_Relay3Label, "3. Relay");

    lv_obj_set_style_text_font(ui_Relay3Label, &ui_font_rubik_light_18, LV_PART_MAIN | LV_STATE_DEFAULT);

}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_MainScreen_screen_init();
    lv_disp_load_scr(ui_MainScreen);
}

