#pragma once
#include <vector>
#include <sstream>

using namespace std;

extern "C" void __declspec(dllexport) getPoints(vector<pair<double, double>> & points, stringstream & in);
