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
	Node(std::string val, sf::Vector2f pos, Shape shape = (Shape)0, bool special = false);
	std::string get_val();
	sf::Vector2f get_pos();
	Shape get_shape();
	bool is_special();

	#define OPEDEF(o) bool operator o (const Node& x) const;
	OPEDEF(>);
	OPEDEF(<);
	OPEDEF(==);
	OPEDEF(!=);
	OPEDEF(>=);
	OPEDEF(<=);
private:
	std::string v;
	sf::Vector2f p;
	Shape s;
	bool special;
};

#endif