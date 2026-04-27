#include <StateMachine/AppSetting.hpp>

AppSetting::AppSetting() {
	background_number = 0;
	speed_number = 1;
	background_speed = 2;
	info_display = 1;
	pseudocode_display = 1;
}

void AppSetting::set_background(int bg) {background_number = bg;}
int AppSetting::get_background() {return background_number;}

void AppSetting::set_speed(int s) { speed_number = s; }
int AppSetting::get_speed() { return speed_number; }

void AppSetting::set_bg_speed(int s) { background_speed = s; }
int AppSetting::get_bg_speed() { return background_speed; }

void AppSetting::set_info_display(int s) { info_display = s; }
int AppSetting::get_info_display() { return info_display; }

void AppSetting::set_pseudocode_display(int s) { pseudocode_display = s; }
int AppSetting::get_pseudocode_display() { return pseudocode_display; }



void AppSetting::next_background() {
	background_number = (background_number + 1) % BACKGROUND_CYCLE;
}
void AppSetting::next_speed() {
	speed_number = (speed_number + 1) % SPEED_CYCLE;
}
void AppSetting::next_bg_speed() {
	background_speed = (background_speed + 1) % BACKGROUND_SPEED_CYCLE;
}
void AppSetting::next_info_display() {
	info_display = (info_display + 1) % INFO_DISPLAY_CYCLE;
}
void AppSetting::next_pseudocode_display() {
	pseudocode_display = (pseudocode_display + 1) % PSEUDOCODE_DISPLAY_CYCLE;
}