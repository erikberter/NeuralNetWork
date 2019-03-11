#pragma once

#include <vector>
#include <string>
#include "neural.h"


class netHandler {

private:
	net nNet;

	std::string configFileN;

	std::vector<int> scheme, actFunctions, nTestFiles; //layers 
	std::vector<std::string> dataFilesN, resultFileN;
	std::vector< std::vector<std::string> > testFilesN, wordFilesN, resultNames;
	std::string temp;
	double maxErr, alpha, neuronWM, momentum;
	int breakIterN, checkIterN;
	int  nIter, nLayers, nDataFiles, testIters;
public:
	netHandler();
	netHandler(std::string configFileNI);
	int readConfig();
	int createNet();
	int setTestCases(int dataFileP);
	int startCycle(int dataFileP);
	int startFileChecking();
};