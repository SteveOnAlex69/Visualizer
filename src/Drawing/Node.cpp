#include <Drawing/Node.hpp>
#include <iostream>
#include <vector>

Node::Node(std::string val, sf::Vector2f pos, Shape shape, bool sp) {
	v = val;
	p = pos;
	s = shape;
	special = sp;
}

std::string Node::get_val() {
	return v;
}

sf::Vector2f Node::get_pos() {
	return p;
}

Shape Node::get_shape() {
	return s;
}

int cmp(Node a, Node b) {
	return (a.get_val() > b.get_val()) - (a.get_val() < b.get_val());
}

bool Node::is_special() { return special; }

#define OPE(o) bool Node::operator o (const Node& x) const {return cmp(*this, x) o 0;}
OPE(> );
OPE(< );
OPE(== );
OPE(!= );
OPE(>= );
OPE(<= );