#include <Node.hpp>
#include <iostream>
#include <vector>

Node::Node(int val, sf::Vector2f pos, Shape shape) {
	v = val;
	p = pos;
	s = shape;
}

int Node::get_val() {
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

#define OPE(o) bool Node::operator o (const Node& x) const {return cmp(*this, x) o 0;}
OPE(> );
OPE(< );
OPE(== );
OPE(!= );
OPE(>= );
OPE(<= );