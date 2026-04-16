#include <StateMachine/AppSetting.hpp>

AppSetting::AppSetting() {
	background_number = 0;
	speed_number = 1;
}

void AppSetting::set_background(int bg) {background_number = bg;}

int AppSetting::get_background() {return background_number;}

void AppSetting::set_speed(int s) { speed_number = s; }
int AppSetting::get_speed() { return speed_number; }

void AppSetting::next_background() {
	background_number = (background_number + 1) % BACKGROUND_CYCLE;
}

void AppSetting::next_speed() {
	speed_number = (speed_number + 1) % SPEED_CYCLE;
}