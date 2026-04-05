
#include <SFML/Graphics.hpp>
#include <Helper.hpp>
#include <intrin.h>

unsigned long long MASK(int i) { return 1ULL << i; }
int GETBIT(int mask, int i) { return ((mask) >> i) & 1; }
int pop_cnt(unsigned long long mask) { return __popcnt(mask); }

float dotProduct(Point2 a, Point2 b) {
	return a.x * b.x + a.y * b.y;
}

float dotProduct(Point3 a, Point3 b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float crossProduct(Point2 a, Point2 b) {
	return getArea(Point2(0, 0), a, b);
}

float getArea(Point2 a, Point2 b, Point2 c) {
	return a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
}

std::ostream& operator << (std::ostream& os, Point2 x) {
	return os << "(" << x.x << ", " << x.y << ")";
}

std::ostream& operator << (std::ostream& os, Point3 x) {
	return os << "(" << x.x << ", " << x.y << ", " << x.z << ")";
}

std::mt19937_64 rng(1);
ll rngesus(ll l, ll r) {
	return (ull)rng() % (r - l + 1) + l;
}

bool equal(float a, float b) {
	return std::abs(a - b) <= 1e-6;
}