#include "PairProjectDLL.h"

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
