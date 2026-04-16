#ifndef HELPER_HPP
#define HELPER_HPP

#include <SFML/Graphics.hpp>
#include <random>
#include <chrono>
#include <iostream>
#include <math.h>

#include <vector>
#include <string>

const sf::Vector2u windowSize = sf::Vector2u(1920, 1200);
const sf::Color BACKGROUND = sf::Color(36, 36, 36);
const sf::Color FIRST_COLOR = sf::Color(230, 230, 230); // WHITE
const sf::Color SECOND_COLOR = sf::Color(220, 180, 220); // PINK
const sf::Color THIRD_COLOR = sf::Color(170, 230, 230); // CYAN
const sf::Color FOURTH_COLOR = sf::Color(200, 100, 100); // RED
const sf::Color FIFTH_COLOR = sf::Color(120, 230, 120); // GREEN
const std::string FONT_PATH = std::string(PROJECT_DIR) + "assets/Font/Consola.ttf";
const std::string ART_PATH = std::string(PROJECT_DIR) + "assets/Art/";
const std::string BACKGROUND_PATH = ART_PATH + "/background.png";
const std::string FOREGROUND_PATH = ART_PATH + "/foreground.png";

const sf::Vector2f screen_center(windowSize.x * 0.5f, windowSize.y * 0.5f);

const sf::Vector2f LINKED_LIST_POS = sf::Vector2f(300, 400);
const sf::Vector2f HASH_MAP_POS = sf::Vector2f(400, 310);
const sf::Vector2f BST_POS = screen_center - sf::Vector2f(0, 300);
const sf::Vector2f AVL_POS = BST_POS;
const sf::Vector2f TRIE_POS = AVL_POS;
const sf::Vector2f GRAPH_ROOT = sf::Vector2f(500, 350);

const int EDGE_WIDTH = 6;
const double PI = atan(1);

const float ANIMATION_TIME = 1.0f;


enum UserCommand {
	NONE = 0, INIT = 1, INSERT = 2, ERASE = 3, SEARCH = 4, CLEAR = 5, UPDATE = 6
};

#define ll long long
#define ull unsigned long long
#define Point2 sf::Vector2f
#define Point3 sf::Vector3f

unsigned long long MASK(int i);
int GETBIT(int mask, int i);
int pop_cnt(unsigned long long mask);
long long max(long long x, long long y);
long long min(long long x, long long y);

float dotProduct(Point2 a, Point2 b);
float dotProduct(Point3 a, Point3 b);

float crossProduct(Point2 a, Point2 b);

float getArea(Point2 a, Point2 b, Point2 c);

std::ostream& operator << (std::ostream& os, Point2 x);
std::ostream& operator << (std::ostream& os, Point3 x); 

ll rngesus(ll l, ll r);

bool equal(float a, float b);

void debug_error(std::string message);

std::vector<std::string> split(std::string s, char delimiter = ' ');

float sigmoid(float epoch);

bool check_valid_string(std::string s); // check if whatever in the textbox is properly formatted

std::vector<std::vector<std::string>> split_to_row(std::string s, char delimiter = ' ');


#endif