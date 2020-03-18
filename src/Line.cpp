#include "Project1.h"


Line::Line(int x_1, int y_1, int x_2, int y_2, string tp, int no) {
	x1 = static_cast<double>(x_1);
	y1 = static_cast<double>(y_1);
	x2 = static_cast<double>(x_2);
	y2 = static_cast<double>(y_2);
	type = tp;
	direction = dBthan(x2, x1);
	a = y2 - y1;
	b = x1 - x2;
	c = x2 * y1 - x1 * y2;
	id = no;
	pro();
}

Line::Line(double A, double B, double C) {
	a = A;
	b = B;
	c = C;
	id = -1;
	pro();
}

void Line::pro() noexcept {
	if (dEqual(b, 0)) {
		k = inf;
	}
	else {
		k = -a / b;
	}

	a2 = pow(a, 2);
	b2 = pow(b, 2);
	a2Ab2 = a2 + b2;
	ab = a * b;
	ac = a * c;
	bc = b * c;
	cos = b / sqrt(a2Ab2);
	sin = a / sqrt(a2Ab2);
}


Point Line::withLine(Line l) {
	const double a2 = l.getA();
	double b2 = l.getB();
	double c2 = l.getC();
	//a2*b!=a*b2
	double deno = (a2 * b - a * b2);
	double y = (a * c2 - a2 * c) / deno;
	double x = (b2 * c - b * c2) / deno;
	Point p(x, y);
	return p;
}

Line::Line() {
	x1 = x2 = y1 = y2 = a = b = c = id = 0;
	type = "Line";
	direction = true;
	pro();
}
