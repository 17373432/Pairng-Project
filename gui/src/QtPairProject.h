#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtPairProject.h"
#include <QChart>
#include <QChartView>
#include <QSplineSeries>
#include <QHBoxLayout>
#include <QValueAxis>
#include <QPaintEvent>
#include <QFileDialog>
#include <string>
#include <sstream>
#include <windows.h>
#include <vector>
#include <QListWidgetItem>
#include <QDebug>
#include "NewQtGuiClass.h"
#include "interface.h"
#include "myException.h"
QT_CHARTS_USE_NAMESPACE

struct Point {
public:
	double x;
	double y;
	Point(double x, double y) {
		this->x = x;
		this->y = y;
	}
};

struct Line {
public:
	double x1;
	double x2;
	double y1;
	double y2;
	char c;
	int state;
	int num;
	Line(double x1, double y1, double x2, double y2, char c, int num) {
		this->x1 = x1;
		this->x2 = x2;
		this->y1 = y1;
		this->y2 = y2;
		this->c = c;
		this->state = 1;
		this->num = num;
	}
	void disable() {
		this->state = 0;
	}
	double getX1() {
		return this->x1;
	}
	double getY1() {
		return this->y1;
	}
	double getX2() {
		return this->x2;
	}
	double getY2() {
		return this->y2;
	}
	char getC() {
		return this->c;
	}
	int getState() {
		return this->state;
	}
	int getNum() {
		return this->num;
	}
	std::string to_string() {
		std::string s = "a";
		s[0] = this->c;
		std::string tmp = s + " " + std::to_string((int)this->x1) + " " + std::to_string((int)this->y1) + " " + std::to_string((int)this->x2) + " " + std::to_string((int)this->y2);
		return tmp;
	}
};

struct Circle {
public:
	double x;
	double y;
	double r;
	int state;
	int num;
	Circle(double x, double y, double r, int num) {
		this->x = x;
		this->y = y;
		this->r = r;
		this->state = 1;
		this->num = num;
	}
	void disable() {
		this->state = 0;
	}
	double getX() {
		return this->x;
	}
	double getY() {
		return this->y;
	}
	double getR() {
		return this->r;
	}
	int getState() {
		return this->state;
	}
	int getNum() {
		return this->num;
	}
	std::string to_string() {
		std::string s = "a";
		s[0] = 'C';
		std::string tmp = s + " " + std::to_string((int)this->x) + " " + std::to_string((int)this->y) + " " + std::to_string((int)this->r);
		return tmp;
	}
};

class QtPairProject : public QMainWindow
{
	Q_OBJECT

public slots:
	void OnTestButtonClick();
	void OnOpenFileButtonClick();
	void removeItems();
	void paintObj();
	void paintPoint();
	void OnOpenButtonClick();
	void getData(QString data);
	void changeRange();
	void clearAll();

signals:
	void sendsignal(QString);

public:
	QtPairProject(QWidget *parent = Q_NULLPTR);

	void build();
	void Paint(int n);
	double transferX(double x);
	double transferY(double y);
	void PaintPoint(QPainter *painter, double x, double y);
	void PaintLine(QPainter *painter, double x1, double y1, double x2, double y2);
	void PaintCircle(QPainter *painter, double x, double y, double r);
	double lengthX();
	double lengthY();
	
	void PaintRay(QPainter *painter, double x1, double y1, double x2, double y2);
	void PaintSegment(QPainter *painter, double x1, double y1, double x2, double y2);
	void remove(QPainter *painter);
	void addGuiCircle(int x, int y, int r);
	void addGuiLines(int x1, int y1, int x2, int y2, char c);
	bool eventFilter(QObject *obj, QEvent *event);
	void widgetPaint();
	

	

private:
	Ui::QtPairProjectClass ui;
	NewQtGuiClass *win;
	QImage image;
	QPixmap pmap;
	const int wide = 800, length = 800;
	const int x_times = 20, y_times = 20;
	int x_max = 100000, y_max = 100000;
	int x_min = -100000, y_min = -100000;
	int offset = 0;
	std::vector <Line> lines;
	std::vector <Circle> circles;
	std::vector <Point> points;
	int num = 1;
	std::map <int, std::pair<char, int>> container;
};

