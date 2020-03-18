#include "Project1.h"

Circle::Circle(int cx, int cy, int cr, int no) {
	Point p(static_cast<double>(cx), static_cast<double>(cy));
	o = p;
	r = static_cast<double>(cr);
	id = no;

	r2 = pow(r, 2);
	xx = 2.0 * cx;
	yy = 2.0 * cy;
	x2Ay2Sr2 = pow(cx, 2) + pow(cy, 2) - r2;
}


vector<Point> Circle::withLine(Line l) {
	vector<Point> s;
	const double x0 = o.getX();
	const double y0 = o.getY();

	const double delta = r2 - pow(l.getA() * x0 + l.getB() * y0 + l.getC(), 2) / l.geta2Ab2();

	if (dBequal(delta, 0)) {
		const double sqrtDelta = sqrt(delta);
		const double leftX = (l.getb2() * x0 - l.getab() * y0 - l.getac()) / l.geta2Ab2();
		const double rightX = sqrtDelta * l.getCos();
		const double leftY = (l.geta2() * y0 - l.getab() * x0 - l.getbc()) / l.geta2Ab2();
		const double rightY = sqrtDelta * l.getSin();
		Point p1(leftX - rightX, leftY + rightY);
		Point p2(leftX + rightX, leftY - rightY);
		s.push_back(p1);
		s.push_back(p2);
	}

	return s;
}

vector<Point> Circle::withCircle(Circle that) {
	vector<Point> s;
	const double max = r + that.r;
	const double min = abs(r - that.r);
	const double d = sqrt(pow(o.getX() - that.o.getX(), 2) + pow(o.getY() - that.o.getY(), 2));

	if (dLequal(min, d) && dLequal(d, max)) {
		const double A = that.xx - xx;
		const double B = that.yy - yy;
		const double C = x2Ay2Sr2 - that.x2Ay2Sr2;
		const Line l(A, B, C);
		s = withLine(l);
	}

	return s;

}

Circle::Circle() {
	id = 0;
	r = 0;

	r2 = pow(r, 2);
	xx = 0;
	yy = 0;
	x2Ay2Sr2 = 0;
}