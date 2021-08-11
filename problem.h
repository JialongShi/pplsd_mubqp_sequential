#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

class problem {
public:
	string problemName;
	int n;
	int m;
	double rho; // objective correlation
	double den; // density
	vector< vector< vector<int> > > Q;

public:
	bool readProblem(const char* filename);
};
