#ifndef UIDESIGN_HPP
#define UIDESIGN_HPP

#include <SFML/Graphics.hpp>
#include <UI/MenuManager.hpp>
#include <UI/UIUnit.hpp>
#include <UI/Button.hpp>
#include <Helper.hpp>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>
#include <concepts>
#include <math.h>


Button* add_text(UIUnit& menu, sf::Vector2f pos, int text_size,
	Alignment align_type, Alignment rel_pos, std::string name, std::string text);
Button* add_button(UIUnit& menu, sf::Vector2f pos, sf::Vector2f size,
	int text_size, Alignment align_type, Alignment rel_pos,
	std::string name, std::string text);
Button* add_text_box(UIUnit& menu, sf::Vector2f pos, sf::Vector2f size,
	int text_size, Alignment align_type, Alignment rel_pos, std::string name);

void setup_menu(UIUnit& menu);
void setup_about(UIUnit& about);
void setup_settings(UIUnit& settings);
void setup_visualizer(UIUnit& visualizer);

std::string spawn_text_box(UIUnit& scene, std::string category);
void despawn_text_box(UIUnit& scene);
void spawn_message_box(UIUnit& scene, std::string message);
void despawn_message_box(UIUnit& scene);
void spawn_form(UIUnit& scene, int text_field_count);
void despawn_form(UIUnit& scene);

#endif