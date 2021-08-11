#pragma once

#include "problem.h"
#include "solution.h"

#include <list>

using namespace std;

class archive
{
public:
	list<solution> solList;

	int unexploredSolNum;
	int inBoundSolNum;
	double bestScalarFuncValue;

public:
	archive();

	void addToArchive(const solution &theSol);

	void deleteFromArchive(list<solution>::iterator &solIt);

	bool judgeRepeatition(const solution &theSol) const;

	bool judgeBeDomd_MaxCase(const solution &theSol) const;

	void updateArchive(const solution &theSol);

	int countUnexploredSolNum();

	int countInBoundSolNum();

	double getBestScalarFuncValue();

	bool loadFromFile(const char* filename);

	bool printToFile(const char* filename);
};


