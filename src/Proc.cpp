#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <unordered_set>
#include "Project1.h"

using namespace std;

Proc::Proc() {
	num = 0;
}

int main(int argc, char* argv[]) {
	int result = 0;
	ifstream in;
	ofstream out;
	if (argc != 5) {
		cout << "Wrong Format!" << endl;
		exit(0);
	}
	if (strcmp(argv[1], "-i") == 0 && strcmp(argv[3], "-o") == 0) {
		in.open(argv[2]);
		out.open(argv[4]);
	}
	else if (strcmp(argv[3], "-i") == 0 && strcmp(argv[1], "-o") == 0) {
		in.open(argv[4]);
		out.open(argv[2]);
	}
	else {
		cout << "Wrong Format!" << endl;
		exit(0);
	}

	if (!in) {
		cout << "Input File Wrong!\n";
		exit(0);
	}

	Proc p;
	result = p.process(in);
	out << result << endl;

	exit(0);
}

int Proc::process(ifstream& in) {
	int n;
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	int r1 = 0;
	char c = '\0';

	in >> n;
	for (int i = 0; i < n; i++) {
		in >> c;
		if (c == 'L') {
			in >> x1 >> y1 >> x2 >> y2;
			Line line(x1, y1, x2, y2, "Line", i);
			preProcLine(line);
		}
		else if (c == 'C') {
			in >> x1 >> y1 >> r1;
			Circle circle(x1, y1, r1, i);
			addCircle(circle);
		}
		else if (c == 'S') {
			in >> x1 >> y1 >> x2 >> y2;
			Line line(x1, y1, x2, y2, "Segment", i);
			preProcLine(line);
		}
		else if (c == 'R') {
			in >> x1 >> y1 >> x2 >> y2;
			Line line(x1, y1, x2, y2, "Ray", i);
			preProcLine(line);
		}
	}
	int result = calcPoint();
	/*
	ofstream fout("cc.txt");
	set<Point>::iterator iter;
	for (iter = pointSet.begin(); iter != pointSet.end(); ++iter) {
		Point p;
		p = *iter;
		if (p.getX() > 32293000000 && p.getX() < 32293400000) {
			vector<int> v = p.getLines();
			for (int i = 0; i < v.size(); i++) {
				cout << v[i] << endl;
			}
		}
		//fout << p.getX() << " " << p.getY() << endl;
	}
	*/
	return result;
}

void Proc::preProcLine(Line line) {
	map<double, vector<Line>>::iterator iter;
	iter = preMap.find(line.getK());
	if (iter != preMap.end()) {
		vector<Line> s = iter->second;
		s.push_back(line);
		preMap[line.getK()] = s;
	}
	else {
		vector<Line> s;
		s.push_back(line);
		preMap[line.getK()] = s;
	}
}


int Proc::calcPoint() {
	lineAndLine();
	calcCircle();
	return pointSet.size();
}

void Proc::lineAndLine() {
	map<double, vector<Line>>::iterator iterM;
	for (iterM = preMap.begin(); iterM != preMap.end(); iterM++) {
		vector<Line>::iterator iterS;
		vector<Line> tempSet = iterM->second;
		//for (iterS = tempSet.begin(); iterS != iterM->second.end(); iterS++)
		for (iterS = tempSet.begin(); iterS != tempSet.end(); iterS++) {
			vector<Line>::iterator iterL;
			Line l1 = *iterS;
			set<int> inteId;
			for (iterL = lineSet.begin(); iterL != lineSet.end(); iterL++) {
				Line l2 = *iterL;
				//if find, it is useless to calculate the intersection
				set<int>::iterator iterI = inteId.find(l2.getId());
				if (iterI != inteId.end()) {
					continue;
				}
				Point p = l1.withLine(l2);
				double p_x = p.getX();
				if (l1.isOnLine(p_x) && l2.isOnLine(p_x)) {
					//set<Point>::iterator iterP = pointSet.find(p);
					unordered_set<Point, hashPoint>::iterator iterP = pointSet.find(p);
					//if find, add all the id of lines intersected at this point to inteId
					if (iterP != pointSet.end()) {
						p = *iterP;
						vector<int> temp = p.getLines();
						inteId.insert(temp.begin(), temp.end());
						p.addLine(l1.getId());
					}
					else {
						p.addLine(l1.getId());
						p.addLine(l2.getId());
						pointSet.insert(p);
					}
				}
			}
		}
		lineSet.insert(lineSet.end(), tempSet.begin(), tempSet.end());
	}
}

void Proc::calcCircle() {
	vector<Circle>::iterator iter1;
	for (iter1 = circleSet.begin(); iter1 != circleSet.end(); iter1++) {
		vector<Circle>::iterator iter2;
		Circle circle1 = *iter1;
		lineAndCircle(circle1);
		for (iter2 = circleSet.begin(); iter2 != iter1; iter2++) {
			Circle circle2 = *iter2;
			vector<Point> s = circle1.withCircle(circle2);
			vector<Point>::iterator iterS;
			for (iterS = s.begin(); iterS != s.end(); iterS++) {
				pointSet.insert(*iterS);
			}
		}
	}
}

void Proc::lineAndCircle(Circle circle) {
	vector<Point> result;
	map<double, vector<Line>>::iterator iterM;
	for (iterM = preMap.begin(); iterM != preMap.end(); iterM++) {
		vector<Line>::iterator iterS;
		vector<Line> tempSet = iterM->second;
		//for (iterS = tempSet.begin(); iterS != iterM->second.end(); iterS++)
		for (iterS = tempSet.begin(); iterS != tempSet.end(); iterS++) {
			Line l = *iterS;
			vector<Point> s = circle.withLine(l);
			vector<Point>::iterator iterS;
			for (iterS = s.begin(); iterS != s.end(); iterS++) {
				double p_x = (*iterS).getX();
				if (l.isOnLine(p_x)) {
					pointSet.insert(*iterS);
				}
			}
		}
	}
}
