// PairProjectUsingDll.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#pragma comment(lib, "PairProjectDll.lib")
#include "pch.h"
#include <iostream>
#include "Project1.h"



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

