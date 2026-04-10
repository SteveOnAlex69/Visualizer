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
	Node(std::string val = "null", sf::Vector2f pos = sf::Vector2f(-1, -1), 
		unsigned long long hash_val = 0, Shape shape = (Shape)0, bool special = false);
	std::string get_val();
	sf::Vector2f get_pos();
	void set_pos(sf::Vector2f pos);
	Shape get_shape();
	bool is_special();

	void set_opacity(float o);
	float get_opacity();

	void set_color(sf::Color color);
	sf::Color get_color();

	unsigned long long get_hash_val();

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
	float opacity;

	unsigned long long hash_value;

	sf::Color node_color;
};

#endif