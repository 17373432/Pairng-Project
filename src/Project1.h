#pragma once
#include <map>
#include <set>
#include <vector>
#include <fstream>
#include <unordered_set>
#include <math.h>

#define eps 0.00000000001
#define inf 1000000

using namespace std;

inline bool dEqual(double x, double y) {
	double temp = 0;
	bool result = false;
	temp = abs(x - y);
	if (temp < eps) {
		result = true;
	}
	return result;
}

inline bool dLequal(double x, double y) {
	return (x < y) || dEqual(x, y);
}

inline bool dBequal(double x, double y) {
	return (x > y) || dEqual(x, y);
}

inline bool dLthan(double x, double y) {
	return !dBequal(x, y);
}

inline bool dBthan(double x, double y) {
	return !dLequal(x, y);
}

class Point {
private:

	vector<int> locateLines;
public:
	double x;
	double y;
	Point(double px, double py);
	Point();
	void addLine(int lineId) {
		locateLines.push_back(lineId);
	}
	inline vector<int> getLines() {
		return locateLines;
	}
	inline bool operator < (const Point right)const {
		bool result = false;
		if (dLthan(x, right.x)) {
			result = true;
		}
		else if (dEqual(x, right.x)) {
			if (dLthan(y, right.y)) {
				result = true;
			}
		}
		return result;
	}
	inline bool operator == (const Point right)const {
		bool result = false;
		if (dEqual(x, right.x) && dEqual(y, right.y)) {
			result = true;
		}
		return result;
	}
	inline double getX() {
		return x;
	}
	inline double getY() {
		return y;
	}

};

class hashPoint {
public:
	std::size_t operator()(const Point& p) const {
		return (hash<double>()(p.x) << 16) + hash<double>()(p.y);
	}
};


class Line {
private:
	double a;
	double b;
	double c;
	double k;
	int id;

	double a2Ab2;
	double b2;
	double ab;
	double ac;
	double a2;
	double bc;
	double cos;
	double sin;

	string type;
	double x1;
	double y1;
	double x2;
	double y2;
	bool direction;

	void pro() noexcept;
public:
	Line(int x1, int y1, int x2, int y2, string tp, int no);
	Line(double A, double B, double C);
	Line();
	bool isOnLine(double x) {
		bool result = true;
		if (type == "Segment") {
			result = dLequal(x1, x) && dLequal(x, x2)
				|| dLequal(x2, x) && dLequal(x, x1);
		}
		else if (type == "Ray") {
			return direction && dBequal(x, x1)
				|| !direction && dLequal(x, x1);
		}
		return result;
	}
	bool operator < (const Line right)const {
		return id < right.id;
	}
	inline double getK() {
		return k;
	}
	inline double getA() {
		return a;
	}
	inline double getB() {
		return b;
	}
	inline double getC() {
		return c;
	}
	inline int getId() {
		return id;
	}

	Point withLine(Line l);

	inline double geta2Ab2() {
		return a2Ab2;
	}
	inline double getb2() {
		return b2;
	}
	inline double getab() {
		return ab;
	}
	inline double getac() {
		return ac;
	}
	inline double geta2() {
		return a2;
	}
	inline double getbc() {
		return bc;
	}
	inline double getCos() {
		return cos;
	}
	inline double getSin() {
		return sin;
	}
};

class Circle {
private:
	Point o;
	double r;
	int id;

	double r2;
	double xx;
	double yy;
	double x2Ay2Sr2;
public:
	Circle(int cx, int cy, int cr, int no);
	Circle();
	vector<Point> withLine(Line l);
	vector<Point> withCircle(Circle that);
	inline bool operator < (const Circle right)const {
		return id < right.id;
	}
};

class Proc {
private:
	map<double, vector<Line>> preMap;
	unordered_set<Point, hashPoint> pointSet;
	//set<Point> pointSet;
	int num;
	vector<Line> lineSet;
	vector<Circle> circleSet;
public:
	Proc();
	int process(ifstream& in);
	void preProcLine(Line line);
	int calcPoint();
	void lineAndLine();
	void addCircle(Circle circle) {
		circleSet.push_back(circle);
	}
	void calcCircle();
	void lineAndCircle(Circle circle);
};
