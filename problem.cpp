#include "problem.h"


using namespace std;

bool problem::readProblem(const char* filename)
{
	problemName = filename;

	FILE *fp = fopen(filename, "r");

	if (fp == NULL) return false;

	char key[256];

	if (fscanf(fp, "%s", &key) != 1) {
		fclose(fp);
		return false;
	}

	while (strlen(key)>1 || strncmp(key, "p", 1)) {

		if (fscanf(fp, "%s", &key) != 1) {
			fclose(fp);
			return false;
		}

	}

	if (fscanf(fp, "%s", &key) != 1) {
		fclose(fp);
		return false;
	}
	if (fscanf(fp, "%lf", &rho) != 1) {
		fclose(fp);
		return false;
	}
	if (fscanf(fp, "%d", &m) != 1) {
		fclose(fp);
		return false;
	}
	if (fscanf(fp, "%d", &n) != 1) {
		fclose(fp);
		return false;
	}
	if (fscanf(fp, "%lf", &den) != 1) {
		fclose(fp);
		return false;
	}
	if (fscanf(fp, "%s", &key) != 1) {
		fclose(fp);
		return false;
	}
	if (fscanf(fp, "%s", &key) != 1) {
		fclose(fp);
		return false;
	}

	Q.resize(m);
	for (int mi = 0; mi < m; ++mi) {
		Q[mi].resize(n);
		for (int i = 0; i < n; ++i) {
			Q[mi][i].resize(n);
			for (int j = 0; j < n; ++j) {
				Q[mi][i][j] = 0;
			}
		}
	}

	for (int j = 0; j < n; ++j) { //each matrix is given by: c(1,1) ... c(N,1) c(1,2) ... c(N,2) ... c(N,N)
		for (int i = 0; i < n; ++i) {
			for (int mi = 0; mi < m; ++mi) {
				int qij;
				if (fscanf(fp, "%d", &qij) != 1) {
					fclose(fp);
					return false;
				}
				Q[mi][i][j] = qij;
			}
		}
	}

	fclose(fp);

	return true;
}


