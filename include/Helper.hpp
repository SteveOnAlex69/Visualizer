#ifndef HELPER_HPP
#define HELPER_HPP

#include <SFML/Graphics.hpp>
#include <random>
#include <chrono>
#include <math.h>

const sf::Vector2u windowSize = sf::Vector2u(1920, 1200);
const sf::Color BACKGROUND = sf::Color(174, 183, 132);
const sf::Color FORESKIN = sf::Color(65, 67, 27);
const std::string FONT_PATH = std::string(PROJECT_DIR) + "assets/Font/Consola.ttf";
const sf::Vector2f screen_center(windowSize.x * 0.5f, windowSize.y * 0.5f);



const int EDGE_WIDTH = 6;
const double PI = atan(1);

#define ll long long
#define ull unsigned long long
#define Point2 sf::Vector2f
#define Point3 sf::Vector3f

float dotProduct(Point2 a, Point2 b);
float dotProduct(Point3 a, Point3 b);

float crossProduct(Point2 a, Point2 b);

float getArea(Point2 a, Point2 b, Point2 c);

std::ostream& operator << (std::ostream& os, Point2 x);
std::ostream& operator << (std::ostream& os, Point3 x); 

ll rngesus(ll l, ll r);

bool equal(float a, float b);

#endif