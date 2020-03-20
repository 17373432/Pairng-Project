#include <iostream>
#include <fstream>
#include "interface.h"
#pragma comment(lib, "core.lib")

using namespace std;

int main(int argc, char* argv[]) {
	int result = 0;
	ifstream in;
	ofstream out;
	if (argc != 5) {
		cout << "Right Format: intersect.exe -i <path to input file> -o <path to output file>\n" << endl;
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
		cout << "Right Format: intersect.exe -i <path to input file> -o <path to output file>\n" << endl;
		exit(0);
	}

	if (!in) {
		cout << "Input File Cannot Open!\n";
		exit(0);
	}

	try {
		istreambuf_iterator<char> beg(in), end;
		string file(beg, end);
		stringstream ss(file);
		vector<pair<double, double>> points;
		getPoints(points, ss);
		result = points.size();
		out << result << endl;
	}
	catch (exception e) {
		e.what();
		exit(0);
	}

	return 0;
}
