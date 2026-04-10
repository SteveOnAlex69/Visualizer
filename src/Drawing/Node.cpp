#include <Drawing/Node.hpp>
#include <Helper.hpp>
#include <iostream>
#include <vector>

const int BASE = 307;

Node::Node(std::string val, sf::Vector2f pos, unsigned long long hash_val, Shape shape, bool sp) {
	v = val;
	p = pos;
	s = shape;
	special = sp;
	opacity = 1;

	hash_value = hash_val;
	for (char c : val) {
		hash_value = hash_value * BASE + c;
	}

	if (sp == 0) node_color = FIRST_COLOR;
	else node_color = SECOND_COLOR;
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

bool Node::is_special() { return special; }


unsigned long long Node::get_hash_val() {
	return hash_value;
}

void Node::set_opacity(float o) { opacity = o; }
float Node::get_opacity() { return opacity; }



void Node::set_color(sf::Color color) { node_color = color; }
sf::Color Node::get_color() { return node_color; }

#define OPE(o) bool Node::operator o (const Node& x) const {return cmp(*this, x) o 0;}
OPE(> );
OPE(< );
OPE(== );
OPE(!= );
OPE(>= );
OPE(<= );