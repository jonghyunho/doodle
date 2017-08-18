#include <iostream>

using namespace std;

struct Point {
	int x, y;
	
	Point() : x(0), y(0) {}
	Point(int _x, int _y) : x(_x), y(_y) {}

	Point operator-(Point& rhs) {
		Point result;
		result.x = x - rhs.x;
		result.y = y - rhs.y;
		return result;
	}

};

int ccw(Point p, Point q) {
	return p.x * q.y - p.y * q.x;
}

int ccw(Point r, Point p, Point q) {
	return ccw(p - r, q - r);
}

bool leftTurn(Point a, Point b, Point c) {
	return ccw(a, b, c) > 0;
}

bool rightTurn(Point a, Point b, Point c) {
	return ccw(a, b, c) < 0;
}

bool collinear(Point a, Point b, Point c) {
	return ccw(a, b, c) == 0;
}

bool between(Point a, Point b, Point c) {
	if (!collinear(a, b, c)) {
		return false;
	}

	if (a.x != b.x) {
		return (a.x <= c.x && c.x <= b.x) ||
					 (b.x <= c.x && c.x <= a.x);
	}
	else {
		return (a.y <= c.y && c.y <= b.y) ||
					 (b.y <= c.y && c.y <= a.y);
	}
}

int direction(Point a, Point b, Point c) {
	int result = ccw(a, b, c);

	if (result < 0) { return -1; }
	else if (result > 0) { return 1; }
	return 0;
}

int intersectProp(Point a, Point b, Point c, Point d) {
	return (direction(a, b, c) * direction(a, b, d) < 0) &&
				 (direction(c, d, a) * direction(c, d, b) < 0);
}

int intersect(Point a, Point b, Point c, Point d) {
	return (direction(a, b, c) * direction(a, b, d) <= 0) &&
				 (direction(c, d, a) * direction(c, d, b) <= 0);
}

int main() {
	return 0;
}
