#ifndef NODE_HPP
#define NODE_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

enum Shape{
	NO = 0,
	CIRCLE = 1,
	SQUARE = 2,
	DIAMOND = 3,
	TRIANGLE = 4
};

class Node {
public:
	Node(int val, sf::Vector2f pos, Shape shape = (Shape)0);
	int get_val();
	sf::Vector2f get_pos();
	Shape get_shape();

	#define OPEDEF(o) bool operator o (const Node& x) const;
	OPEDEF(>);
	OPEDEF(<);
	OPEDEF(==);
	OPEDEF(!=);
	OPEDEF(>=);
	OPEDEF(<=);
private:
	int v;
	sf::Vector2f p;
	Shape s;
};

#endif