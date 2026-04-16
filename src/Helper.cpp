#include <SFML/Graphics.hpp>
#include <Helper.hpp>
#include <intrin.h>

unsigned long long MASK(int i) { return 1ULL << i; }
int GETBIT(int mask, int i) { return ((mask) >> i) & 1; }
int pop_cnt(unsigned long long mask) { return __popcnt(mask); }

long long max(long long x, long long y) { return std::max(x, y); }
long long min(long long x, long long y) { return std::min(x, y); }

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

void debug_error(std::string message){
	std::cout << message << std::endl;
	exit(1);
}

std::vector<std::string> split(std::string s, char delimiter) {
	std::vector<std::string> ans;
	for (char c : s) {
		if (c == delimiter) ans.emplace_back();
		else if (c == '\n') {
			ans.push_back("\n");
			ans.push_back("");
		}
		else {
			if (ans.empty()) debug_error("splitting string gone wrong");
			ans.back().push_back(c);
		}
	}
	return ans;
}


std::vector<std::vector<std::string>> split_to_row(std::string s, char delimiter) {
	std::vector<std::string> vcl = split(s, delimiter);
	std::vector<std::vector<std::string>> ans;
	ans.emplace_back();
	for (auto i : vcl) {
		if (i.empty()) continue;
		if (i == "\n") {
			if (ans.back().size()) ans.emplace_back();
		}
		else {
			ans.back().push_back(i);
		}
	}
	return ans;
}


float sigmoid(float epoch) {
	epoch -= ANIMATION_TIME * 0.5F;
	epoch *= 10 / ANIMATION_TIME;
	return (float)1 / (1 + std::exp(-epoch));
}

bool check_valid_string(std::string s) {
	std::vector<std::string> p = split(" " + s);
	for (auto i : p) if (i.size() > 4) return false;
	return true;
}