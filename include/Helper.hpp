#ifndef HELPER_HPP
#define HELPER_HPP

#include <SFML/Graphics.hpp>
#include <random>
#include <chrono>
#include <math.h>

const sf::Vector2u windowSize = sf::Vector2u(1920, 1200);
const sf::Color BACKGROUND = sf::Color(36, 36, 36);
const sf::Color FIRST_COLOR = sf::Color(230, 230, 230);
const sf::Color SECOND_COLOR = sf::Color(170, 170, 230);
const std::string FONT_PATH = std::string(PROJECT_DIR) + "assets/Font/Consola.ttf";
const sf::Vector2f screen_center(windowSize.x * 0.5f, windowSize.y * 0.5f);

const sf::Vector2f LINKED_LIST_POS = sf::Vector2f(300, 400);
const sf::Vector2f HASH_MAP_POS = sf::Vector2f(500, 350);
const sf::Vector2f BST_POS = screen_center - sf::Vector2f(0, 300);
const sf::Vector2f AVL_POS = BST_POS;
const sf::Vector2f TRIE_POS = AVL_POS;

const int EDGE_WIDTH = 6;
const double PI = atan(1);

const float ANIMATION_TIME = 1;

#define ll long long
#define ull unsigned long long
#define Point2 sf::Vector2f
#define Point3 sf::Vector3f

unsigned long long MASK(int i);
int GETBIT(int mask, int i);
int pop_cnt(unsigned long long mask);

float dotProduct(Point2 a, Point2 b);
float dotProduct(Point3 a, Point3 b);

float crossProduct(Point2 a, Point2 b);

float getArea(Point2 a, Point2 b, Point2 c);

std::ostream& operator << (std::ostream& os, Point2 x);
std::ostream& operator << (std::ostream& os, Point3 x); 

ll rngesus(ll l, ll r);

bool equal(float a, float b);

#endif