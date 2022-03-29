#include<time.h>
#include "ui.h"

void NAV_BTTN_ENABLE(struct _lv_obj_t * bttn, struct _lv_obj_t * icon) {
	lv_obj_set_style_bg_color(bttn, lv_color_hex(0x2DAB66), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(bttn, LV_GRAD_DIR_VER, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(icon, lv_color_hex(0x141414), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(icon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
}
void NAV_BTTN_DISABLE(struct _lv_obj_t * bttn, struct _lv_obj_t * icon) {
	lv_obj_set_style_bg_color(bttn, lv_color_hex(0x141414), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(bttn, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(icon, lv_color_hex(0x888888), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor_opa(icon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
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

void LOADSCREEN(lv_event_t * e) {
	NAV_BTTN_ENABLE(ui_NavButton1, ui_NavIcon1);

	lv_bar_set_value(ui_Level1, 50, LV_ANIM_OFF);
	lv_label_set_text_fmt(ui_Level1State, "%d%%", 50);

	lv_bar_set_value(ui_Level2, 50, LV_ANIM_OFF);
	lv_label_set_text_fmt(ui_Level2State, "%d%%", 50);
	
	lv_label_set_text_fmt(ui_DateIndicator, "%d%%", 50);


	time_t t;
    t = time(NULL);
    struct tm tm;
	tm = *localtime(&t);
	lv_label_set_text_fmt(ui_TimeIndicator, "%02d:%02d", tm.tm_hour, tm.tm_min);
	lv_label_set_text_fmt(ui_DateIndicator, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
}

void ONCLICK_NAV_1(lv_event_t * e) {
	NAV_BTTN_ENABLE(ui_NavButton1, ui_NavIcon1);
	NAV_BTTN_DISABLE(ui_NavButton2, ui_NavIcon2);
	NAV_BTTN_DISABLE(ui_NavButton3, ui_NavIcon3);
	NAV_BTTN_DISABLE(ui_NavButton4, ui_NavIcon4);
	NAV_BTTN_DISABLE(ui_NavButton5, ui_NavIcon5);
}

void ONCLICK_NAV_2(lv_event_t * e) {
	NAV_BTTN_DISABLE(ui_NavButton1, ui_NavIcon1);
	NAV_BTTN_ENABLE(ui_NavButton2, ui_NavIcon2);
	NAV_BTTN_DISABLE(ui_NavButton3, ui_NavIcon3);
	NAV_BTTN_DISABLE(ui_NavButton4, ui_NavIcon4);
	NAV_BTTN_DISABLE(ui_NavButton5, ui_NavIcon5);
}

void ONCLICK_NAV_3(lv_event_t * e) {
	NAV_BTTN_DISABLE(ui_NavButton1, ui_NavIcon1);
	NAV_BTTN_DISABLE(ui_NavButton2, ui_NavIcon2);
	NAV_BTTN_ENABLE(ui_NavButton3, ui_NavIcon3);
	NAV_BTTN_DISABLE(ui_NavButton4, ui_NavIcon4);
	NAV_BTTN_DISABLE(ui_NavButton5, ui_NavIcon5);
}

void ONCLICK_NAV_4(lv_event_t * e) {
	NAV_BTTN_DISABLE(ui_NavButton1, ui_NavIcon1);
	NAV_BTTN_DISABLE(ui_NavButton2, ui_NavIcon2);
	NAV_BTTN_DISABLE(ui_NavButton3, ui_NavIcon3);
	NAV_BTTN_ENABLE(ui_NavButton4, ui_NavIcon4);
	NAV_BTTN_DISABLE(ui_NavButton5, ui_NavIcon5);
}
void ONCLICK_NAV_5(lv_event_t * e) {
	NAV_BTTN_DISABLE(ui_NavButton1, ui_NavIcon1);
	NAV_BTTN_DISABLE(ui_NavButton2, ui_NavIcon2);
	NAV_BTTN_DISABLE(ui_NavButton3, ui_NavIcon3);
	NAV_BTTN_DISABLE(ui_NavButton4, ui_NavIcon4);
	NAV_BTTN_ENABLE(ui_NavButton5, ui_NavIcon5);
}
 
void PREFILL_SETTINGS(lv_event_t * e) {
	lv_obj_add_state(ui_MqttEnabled, LV_STATE_CHECKED);
	lv_textarea_set_text(ui_MqttHost, "1.2.3.4");
	lv_textarea_set_text(ui_MqttUsername, "admin");
	lv_textarea_set_text(ui_MqttPassword, "pass");

	lv_obj_add_state(ui_EnableFreshWater, LV_STATE_CHECKED);
	lv_textarea_set_text(ui_FreshWaterTopic, "level/fresh");

	lv_obj_add_state(ui_EnableGrayWater, LV_STATE_CHECKED);
	lv_textarea_set_text(ui_GreyWaterTopic, "level/grey");
}
