#include <Drawing/Node.hpp>
#include <Helper.hpp>
#include <iostream>
#include <vector>

const int BASE = 307;

Node::Node(std::string val, sf::Vector2f pos, unsigned long long hash_val, Shape shape, int sp) {
	v = val;
	p = pos;
	s = shape;
	set_special(sp);
	opacity = 1;

	hash_value = hash_val;
	if (hash_value == 0) {
		for (auto c : val)
			hash_value = hash_value * 10 + (c - '0');
	}


}

void Node::set_special(int sp) {
	special = sp;
	switch (sp) {
	case 0:
		node_color = font_color = FIRST_COLOR;
		bg_color = BACKGROUND;
		break;
	case 1:
		node_color = font_color = THIRD_COLOR;
		bg_color = BACKGROUND;
		break;
	case 2:
		node_color = bg_color = FOURTH_COLOR;
		font_color = BACKGROUND;
		break;
	case 3:
		node_color = bg_color = FIFTH_COLOR;
		font_color = BACKGROUND;
		break;
	}
}

std::string Node::get_val() {
	return v;
}

sf::Vector2f Node::get_pos() {
	return p;
}

void Node::set_pos(sf::Vector2f pos) {
	p = pos;
}

Shape Node::get_shape() {
	return s;
}

int cmp(Node a, Node b) {
	return (a.get_val() > b.get_val()) - (a.get_val() < b.get_val());
}

int Node::is_special() { return special; }


unsigned long long Node::get_hash_val() {
	return hash_value;
}

void Node::set_opacity(float o) { opacity = o; }
float Node::get_opacity() { return opacity; }



void Node::set_color(sf::Color color) { node_color = color; }
sf::Color Node::get_color() { return node_color; }
void Node::set_font_color(sf::Color color) { font_color = color; }
sf::Color Node::get_font_color() { return font_color; }
void Node::set_background_color(sf::Color color) { bg_color = color; }
sf::Color Node::get_background_color() { return bg_color; }


#define OPE(o) bool Node::operator o (const Node& x) const {return cmp(*this, x) o 0;}
OPE(> );
OPE(< );
OPE(== );
OPE(!= );
OPE(>= );
OPE(<= );


void Node::set_weight(std::string w) {
	weight = w;
}
std::string Node::get_weight() {
	return weight;
}