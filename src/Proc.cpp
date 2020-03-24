#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <unordered_set>
#include <regex>
#include "Project1.h"
#include "myException.h"
#include <iomanip>

using namespace std;

bool outOfRange(int x) {
	return x <= -100000 || x >= 100000;
}

int core(string name) {
	//vector<pair<double, double>> core(string name) {
	int result = 0;
	ifstream in;

	in.open(name);

	if (!in) {
		cout << "Input File Cannot Open!\n";
		exit(0);
	}
	vector<pair<double, double>> points;
	try {
		istreambuf_iterator<char> beg(in), end;
		string file(beg, end);
		stringstream ss(file);

		getPoints(points, ss);
		result = points.size();
		cout << result << endl;
	}
	catch (InputException e) {
		e.what();
		//exit(0);
	}
	//return points;
	return result;
}

Proc::Proc() {
	num = 0;
}

void getPoints(vector<pair<double, double>>& result, stringstream& in) {
	Proc p;
	p.process(in);

	p.getPointSet(result);

	//unordered_set<Point, hashPoint> pSet = p.getPointSet();

}

int main(int argc, char* argv[]) {
	int result = 0;
	string inname, outname;
	ofstream out;
	if (argc != 5) {
		cout << "Right Format: intersect.exe -i <path to input file> -o <path to output file>\n" << endl;
		exit(0);
	}
	if (strcmp(argv[1], "-i") == 0 && strcmp(argv[3], "-o") == 0) {
		inname = argv[2];
		outname = argv[4];
	}
	else if (strcmp(argv[3], "-i") == 0 && strcmp(argv[1], "-o") == 0) {
		inname = argv[4];
		outname = argv[2];
	}
	else {
		cout << "Right Format: intersect.exe -i <path to input file> -o <path to output file>\n" << endl;
		exit(0);
	}

	out.open(outname);

	result = core(inname);
	out << result << endl;

	/*
	vector<pair<double, double>> v = core(inname);
	out << v.size() << endl;
	*/
	/*
	out << setiosflags(ios::fixed) << setprecision(5);
	for (int i = 0; i < v.size(); i++) {
		out << v[i].first << "," << v[i].second << endl;
	}
	*/


	return 0;
}

void Proc::process(stringstream& fin) {
	vector<pair<double, double>> result;
	int n;
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	int r1 = 0;
	char c = '\0';

	if (fin.str() == "\0") {
		throw EmptyFileException();
	}

	//fin >> n;
	try {
		string nstr;
		getline(fin, nstr);
		n = stoi(nstr);
	}
	catch (exception e) {
		throw NoNException();
	}
	if (n < 1 || n > 500000) {
		throw NumberException();
	}
	/*
	stringstream s_in;
	string str;
	in >> str;
	s_in << str;

	string str1;
	int i = 0;
	do {
		getline(s_in, str1);
		i++;
	} while ();
	*/
	string str;
	for (int i = 0; i < n; i++) {
		while (true) {
			if (fin.eof()) {
				throw NumOfObjException();
			}
			getline(fin, str);
			if (str.size() != 0) {
				break;
			}
		}
		// 前导0需要去除么
		string pattern("^\\s*([LRS](\\s+(-|\\+)?(([1-9]\\d*)|0)){4}|[C](\\s+(-|\\+)?(([1-9]\\d*)|0)){3})\\s*$");
		regex r(pattern);
		if (!regex_match(str, r)) {
			throw FormatException(i + 1, str);
		}

		stringstream in(str);

		in >> c;
		if (c == 'L') {
			in >> x1 >> y1 >> x2 >> y2;
			if (outOfRange(x1) || outOfRange(y1) || outOfRange(x2) || outOfRange(y2)) {
				throw OutOfRangeException(i + 1, str);
			}
			if (x1 == x2 && y1 == y2) {
				throw CoincideException(i + 1, str);
			}
			Line line(x1, y1, x2, y2, "Line", i);
			if (!preProcLine(line)) {
				throw CoverException(i + 1, str);
			}
		}
		else if (c == 'C') {
			in >> x1 >> y1 >> r1;
			if (outOfRange(x1) || outOfRange(y1) || outOfRange(r1)) {
				throw OutOfRangeException(i + 1, str);
			}
			if (dLequal(r1, 0)) {
				throw LessThanZeroException(i + 1, str);
			}
			Circle circle(x1, y1, r1, i);

			string cstr = to_string(x1) + " " + to_string(y1) + " " + to_string(r1);
			unordered_set<string>::iterator iterC;
			iterC = circles.find(cstr);
			if (iterC != circles.end()) {
				throw CoverException(i + 1, str);
			}
			circles.insert(cstr);

			addCircle(circle);
		}
		else if (c == 'S') {
			in >> x1 >> y1 >> x2 >> y2;
			if (outOfRange(x1) || outOfRange(y1) || outOfRange(x2) || outOfRange(y2)) {
				throw OutOfRangeException(i + 1, str);
			}
			if (x1 == x2 && y1 == y2) {
				throw CoincideException(i + 1, str);
			}
			Line line(x1, y1, x2, y2, "Segment", i);
			if (!preProcLine(line)) {
				throw CoverException(i + 1, str);
			}
		}
		else if (c == 'R') {
			in >> x1 >> y1 >> x2 >> y2;
			if (outOfRange(x1) || outOfRange(y1) || outOfRange(x2) || outOfRange(y2)) {
				throw OutOfRangeException(i + 1, str);
			}
			if (x1 == x2 && y1 == y2) {
				throw CoincideException(i + 1, str);
			}
			Line line(x1, y1, x2, y2, "Ray", i);
			if (!preProcLine(line)) {
				throw CoverException(i + 1, str);
			}
		}
	}

	while (!fin.eof()) {
		getline(fin, str);
		if (str.size() != 0) {
			throw NumOfObjException();
		}
	}
	calcPoint();
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
}

bool Proc::preProcLine(Line line) {
	bool result = true;
	/*map<double, vector<Line>>::iterator iter;
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
	}*/
	unordered_map<pair<double, double>, vector<Line>>::iterator iter;
	pair<double, double> p(line.getXintercept(), line.getYintercept());
	iter = lines.find(p);
	if (iter != lines.end()) {
		vector<Line> s = iter->second;
		for (int i = 0; i < int(s.size()); i++) {
			if (isCover(s[i], line)) {
				result = false;
				break;
			}
		}
		s.push_back(line);
		lines[p] = s;
	}
	else {
		vector<Line> s;
		s.push_back(line);
		lines[p] = s;
	}
	lineSet.push_back(line);
	return result;
}

void Proc::calcPoint() {
	lineAndLine();
	calcCircle();
}

void Proc::lineAndLine() {
	/*map<double, vector<Line>>::iterator iterM;
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
	*/
	vector<Line>::iterator iter1;
	for (iter1 = lineSet.begin(); iter1 != lineSet.end(); iter1++) {
		vector<Line>::iterator iter2;
		//for (iter2 = lineSet.begin(); iter2 != iter1; iter2++) {
		for (iter2 = iter1 + 1; iter2 != lineSet.end(); iter2++) {
			Line l1 = *iter1;
			Line l2 = *iter2;
			double k1 = l1.getK();
			double k2 = l2.getK();

			// 平行线段和射线可能会有交点
			if (dEqual(k1, k2)) {
				continue;
			}
			Point p = l1.withLine(l2);
			double p_x, p_y;
			p_x = p.getX();
			p_y = p.getY();
			/*
			if (dEqual(p_x, 1071.8) && dEqual(p_y, -26.6)) {
				int xxx;
				xxx = 1;
			}*/
			if (l1.isOnLine(p_x, p_y) && l2.isOnLine(p_x, p_y)) {
				pointSet.insert(p);
			}
		}
	}
}

void Proc::calcCircle() {
	vector<Circle>::iterator iter1;
	for (iter1 = circleSet.begin(); iter1 != circleSet.end(); iter1++) {
		vector<Circle>::iterator iter2;
		Circle circle1 = *iter1;
		lineAndCircle(circle1);
		for (iter2 = iter1 + 1; iter2 != circleSet.end(); iter2++) {
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
	/*vector<Point> result;
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
	*/
	vector<Line>::iterator iter;
	for (iter = lineSet.begin(); iter != lineSet.end(); iter++) {
		Line l = *iter;
		vector<Point> s = circle.withLine(l);
		vector<Point>::iterator iterS;
		for (iterS = s.begin(); iterS != s.end(); iterS++) {
			double p_x, p_y;
			p_x = (*iterS).getX();
			p_y = (*iterS).getY();
			/*if (dEqual(p_x, 1071.8) && dEqual(p_y, -26.6)) {
				int xxx;
				xxx = 1;
			}*/
			if (l.isOnLine(p_x, p_y)) {
				pointSet.insert(*iterS);
			}
		}
	}
}

bool Proc::isCover(Line l1, Line l2) {
	bool result = true;
	string tp1 = l1.getType();
	string tp2 = l2.getType();
	double x1_1 = l1.getX1();
	double x2_1 = l1.getX2();
	double x1_2 = l2.getX1();
	double x2_2 = l2.getX2();
	if (!dEqual(l1.getK(), l2.getK())) {
		return false;
	}
	if (tp1 == "Segment" && tp2 == "Segment") {
		if (dBthan(x1_1, x2_1)) {
			if (dBthan(x1_2, x2_2)) {
				if (dBequal(x2_2, x1_1)) {
					if (dEqual(x2_2, x1_1)) {
						Point p(x1_1, l1.getY1());
						pointSet.insert(p);
					}
					result = false;
				}
				else if (dBequal(x2_1, x1_2)) {
					if (dEqual(x2_1, x1_2)) {
						Point p(x2_1, l1.getY2());
						pointSet.insert(p);
					}
					result = false;
				}
			}
			else {
				if (dBequal(x1_2, x1_1)) {
					if (dEqual(x1_2, x1_1)) {
						Point p(x1_1, l1.getY1());
						pointSet.insert(p);
					}
					result = false;
				}
				else if (dBequal(x2_1, x2_2)) {
					if (dEqual(x2_1, x2_2)) {
						Point p(x2_1, l1.getY2());
						pointSet.insert(p);
					}
					result = false;
				}
			}
		}
		else {
			if (dBthan(x1_2, x2_2)) {
				if (dBequal(x2_2, x2_1)) {
					if (dEqual(x2_2, x2_1)) {
						Point p(x2_1, l1.getY2());
						pointSet.insert(p);
					}
					result = false;
				}
				else if (dBequal(x1_1, x1_2)) {
					if (dEqual(x1_1, x1_2)) {
						Point p(x1_1, l1.getY1());
						pointSet.insert(p);
					}
					result = false;
				}
			}
			else {
				if (dBequal(x1_2, x2_1)) {
					if (dEqual(x1_2, x2_1)) {
						Point p(x2_1, l1.getY2());
						pointSet.insert(p);
					}
					result = false;
				}
				else if (dBequal(x1_1, x2_2)) {
					if (dEqual(x1_1, x2_2)) {
						Point p(x1_1, l1.getY1());
						pointSet.insert(p);
					}
					result = false;
				}
			}
		}
	}
	else if (tp1 == "Ray" && tp2 == "Ray") {
		bool dir1 = l1.getDir();
		bool dir2 = l2.getDir();
		if (dir1 == true && dir2 == false) {
			if (dBequal(x1_1, x1_2)) {
				if (dEqual(x1_1, x1_2)) {
					Point p(x1_1, l1.getY1());
					pointSet.insert(p);
				}
				result = false;
			}
		}
		else if (dir1 == false && dir2 == true) {
			if (dBequal(x1_2, x1_1)) {
				if (dEqual(x1_2, x1_1)) {
					Point p(x1_1, l1.getY1());
					pointSet.insert(p);
				}
				result = false;
			}
		}
	}
	else if (tp1 == "Ray" && tp2 == "Segment") {
		bool dir1 = l1.getDir();
		if (dir1) {
			if (dBequal(x1_1, x1_2) && dBequal(x1_1, x2_2)) {
				if (dEqual(x1_1, x1_2) || dEqual(x1_1, x2_2)) {
					Point p(x1_1, l1.getY1());
					pointSet.insert(p);
				}
				result = false;
			}
		}
		else {
			if (dLequal(x1_1, x1_2) && dLequal(x1_1, x2_2)) {
				if (dEqual(x1_1, x1_2) || dEqual(x1_1, x2_2)) {
					Point p(x1_1, l1.getY1());
					pointSet.insert(p);
				}
				result = false;
			}
		}
	}
	else if (tp1 == "Segment" && tp2 == "Ray") {
		bool dir2 = l2.getDir();
		if (dir2) {
			if (dBequal(x1_2, x1_1) && dBequal(x1_2, x2_1)) {
				if (dEqual(x1_2, x1_1) || dEqual(x1_2, x2_1)) {
					Point p(x1_2, l2.getY1());
					pointSet.insert(p);
				}
				result = false;
			}
		}
		else {
			if (dLequal(x1_2, x1_1) && dLequal(x1_2, x2_1)) {
				if (dEqual(x1_2, x1_1) || dEqual(x1_2, x2_1)) {
					Point p(x1_2, l2.getY1());
					pointSet.insert(p);
				}
				result = false;
			}
		}
	}
	return result;
}
