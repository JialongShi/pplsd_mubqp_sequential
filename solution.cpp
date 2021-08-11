#include "solution.h"

using namespace std;

solution::solution() {
	explored = false;
	scalarFunctionValue = -DBL_MAX;
	cosAngleToWV = ILLEGAL_COS;
	inBoundFlag = false;
}

void solution::randomInitialize(const problem& inst) {
	
	x.resize(inst.n);
	for (vector<int>::iterator it = x.begin(); it != x.end(); ++it) {
		*it = rand() % 2;
	}
	calculateFitness(inst);
}


bool solution::calculateFitness(const problem& inst) {
	
	int n = inst.n;
	int m = inst.m;
	if (x.size() != n) {
		return false;
	}

	int i, j, qij;

	fitness.resize(m);
	for (int mi = 0; mi < m; mi++) {
		fitness[mi] = 0;
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				qij = inst.Q[mi][i][j];
				fitness[mi] += x[i] * qij * x[j];
			}
		}
	}
	return true;
}



bool solution::judgeDominate(const solution &sol2) const {
	//verify whether fitness vector A dominate fitness vector B
	if (fitness.size() != sol2.fitness.size()) {
		return false;
	}
	bool allFlag, anyFlag;

	//if A dominate B, means all(A[i]>=B[i]) && any(A[i]>B[i])

	allFlag = true;
	anyFlag = false;

	for (int mi = 0; mi < fitness.size(); mi++) {
		if (fitness[mi] > sol2.fitness[mi]) {
			anyFlag = true;
		}
		if (fitness[mi] < sol2.fitness[mi]) {
			allFlag = false;
			break;
		}
	}
	return allFlag && anyFlag;
}

bool solution::judgeSameSol(const solution &sol2) const {
	if (fitness.size() != sol2.fitness.size() || x.size() != sol2.x.size()) {
		return false;
	}
	int m = fitness.size();
	int n = x.size();

	for (int mi = 0; mi < m; mi++) {
		if (fitness[mi] != sol2.fitness[mi]) {
			return false;
		}
	}
	for (int i = 0; i < n; i++) {
		if (x[i] != sol2.x[i]) {
			return false;
		}
	}

	return true;
}

bool solution::judgeSameFit(const vector<double> &fit2) const {
	if (fitness.size() != fit2.size()) {
		return false;
	}
	int m = fitness.size();

	for (int mi = 0; mi < m; mi++) {
		if (fitness[mi] != fit2[mi]) {
			return false;
		}
	}

	return true;
}








