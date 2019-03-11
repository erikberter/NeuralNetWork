#include "neural.h"
#include "handler.h"

#include "imported/json.hpp"

#include <fstream>
#include <string>
#include <sstream>

using json = nlohmann::json;

netHandler::netHandler() {
	configFileN = "config";
	//default Options
	breakIterN = 10000000;
	checkIterN = 1000;
}


netHandler::netHandler(std::string configFileNI) {
	configFileN = configFileNI;
	//Default Options
	breakIterN = 10000000;
	checkIterN = 1000;
}

int netHandler::readConfig() {
	json j;
	
	std::ifstream i(configFileN+".json");
	i >> j;
	
	scheme = j["net"].get<std::vector<int> >();
	actFunctions = j["actFunctions"].get<std::vector<int> >();
	testFilesN = j["testFile"].get<std::vector<std::vector<std::string> > >();
	wordFilesN = j["wordFile"].get<std::vector<std::vector<std::string> > >();
	resultNames = j["dataOutputName"].get<std::vector<std::vector<std::string> > >();
	dataFilesN = j["dataTestFile"].get<std::vector<std::string> >();
	resultFileN = j["resultFile"].get<std::vector<std::string> >();
	maxErr = j["maxErr"].get<double>();
	alpha = j["alpha"].get<double>();
	momentum = j["momentum"].get<double>();
	neuronWM = j["neuronWM"].get<double>();
	breakIterN = j["breakIterN"].get<int>();
	checkIterN = j["checkIterN"].get<int>();
	nIter = j["iterN"].get<int>();
	nLayers = scheme.size();
	nTestFiles = j["nTestFiles"].get<std::vector<int> >();
	nDataFiles = j["nDataFiles"].get<int>();
	testIters = j["testIters"].get<int>();

	return 0;
}

int netHandler::createNet() {
	nNet = net(scheme, alpha, momentum,  actFunctions, neuronWM, testIters);
	return 0;
}

int netHandler::setTestCases(int dataFileP) {
	nNet.setDataInfo(dataFilesN[dataFileP]);
	return 0;
}

int netHandler::startCycle(int dataFileP){
	int iter = 0, testA = 0;
	std::vector<double> totalTestV(nTestFiles[dataFileP], 0);
	
	for (int i = 0; i < nIter; i++) {
		iter += nNet.train(maxErr, checkIterN, breakIterN);
		
		for (int nTestFilesi = 0; nTestFilesi < nTestFiles[dataFileP]; nTestFilesi++)
			totalTestV[nTestFilesi] += nNet.letMeTry(testFilesN[dataFileP][nTestFilesi]);
		nNet.resetNet();
	}
	std::string schemeS = "";
	for (int i = 0; i < nLayers - 1; i++) 
		schemeS += std::to_string(scheme[i]) + "->";
	
	schemeS += std::to_string(scheme[nLayers - 1]);

	for (int nTestFilesi = 0; nTestFilesi < nTestFiles[dataFileP]; nTestFilesi++) {
		std::ofstream outfile;
		outfile.open("./results/" + resultFileN[dataFileP], std::ios_base::app);
		std::cout << "Grabando el file " << resultNames[dataFileP][nTestFilesi] << std::endl;

		std::string line = "";
		line += resultNames[dataFileP][nTestFilesi] + "::";
		line += schemeS + "::";
		line += std::to_string((int)(iter / nIter)) + "::";
		line += std::to_string((double)(totalTestV[nTestFilesi] / nIter)) + "\n";
		outfile << line;
		outfile.close();

	}
	std::cout << "archivo creado s" << std::endl;
	return 0;
}

int netHandler::startFileChecking(){
	for(int i =0 ; i < nDataFiles; i++){
		setTestCases(i);
		startCycle(i);
	}
}