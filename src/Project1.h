#pragma once
#include <map>
#include <set>
#include <vector>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <math.h>

#define eps 0.00000000001
#define inf 1000000

using namespace std;

inline long long dround(double x) {
	long long result;
	result = (long long)((floor)(x * 10000.000f + 0.5));
	return result;
}

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
		long long x, y;
		x = dround(p.x);
		y = dround(p.y);
		auto h1 = std::hash<long long>{}(x);
		auto h2 = std::hash<long long>{}(y);
		return h1 ^ h2;
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
	double x_intercept;
	double y_intercept;

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
	inline bool isOnLine(double x, double y) {
		bool result = true;

		if (type == "Segment") {
			if (!dEqual(x1, x2)) {
				result = dLequal(x1, x) && dLequal(x, x2)
					|| dLequal(x2, x) && dLequal(x, x1);
			}
			else {
				result = dLequal(y1, y) && dLequal(y, y2)
					|| dLequal(y2, y) && dLequal(y, y1);
			}
		}
		else if (type == "Ray") {
			if (!dEqual(x1, x2)) {
				result = direction && dBequal(x, x1)
					|| !direction && dLequal(x, x1);
			}
			else {
				result = dBthan(y2, y1) && dBequal(y, y1)
					|| dLthan(y2, y1) && dLequal(y, y1);
			}
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
	inline double getXintercept() {
		return x_intercept;
	}
	inline double getYintercept() {
		return y_intercept;
	}
	inline string getType() {
		return type;
	}
	inline double getX1() {
		return x1;
	}
	inline double getY1() {
		return y1;
	}
	inline double getX2() {
		return x2;
	}
	inline double getY2() {
		return y2;
	}
	inline bool getDir() {
		return direction;
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

struct pair_hash
{
	template<class T1, class T2>
	std::size_t operator() (const std::pair<T1, T2>& p) const
	{
		long long first, second;
		first = dround(p.first);
		second = dround(p.second);
		auto h1 = std::hash<long long>{}(first);
		auto h2 = std::hash<long long>{}(second);
		return h1 ^ h2;
	}
};

class Proc {
private:
	unordered_map<pair<double, double>, vector<Line>, pair_hash> lines;
	unordered_set<string> circles;
	map<double, vector<Line>> preMap;
	unordered_set<Point, hashPoint> pointSet;
	//set<Point> pointSet;
	int num;
	vector<Line> lineSet;
	vector<Circle> circleSet;
public:
	Proc();
	void process(stringstream& in);
	bool preProcLine(Line line);
	void calcPoint();
	void lineAndLine();
	void addCircle(Circle circle) {
		circleSet.push_back(circle);
	};
	void calcCircle();
	void lineAndCircle(Circle circle);
	bool isCover(Line l1, Line l2);
	/*
	unordered_set<Point, hashPoint> getPointSet() {
		return pointSet;
	}*/
	void getPointSet(vector<pair<double, double>>& v) {
		unordered_set<Point, hashPoint>::iterator iter;
		for (iter = pointSet.begin(); iter != pointSet.end(); iter++) {
			Point point = *iter;
			pair<double, double> p(point.getX(), point.getY());
			v.push_back(p);
		}
	}
};
void getPoints(vector<pair<double, double>>& result, stringstream& in);
int core(string name);
//vector<pair<double, double>> core(string name);
