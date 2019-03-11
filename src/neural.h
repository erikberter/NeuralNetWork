#ifndef __NEURAL__H__
#define __NEURAL__H__

#include <iostream>
#include <vector>


class net {
private:
	double alpha, momentum, neuronWM;
	int maxInp, nLayers, testIters;
	std::vector<int> layers, actFunctions;
	std::vector<std::vector<double> > layerVals, layerValsA, Deltas;
	std::vector< std::vector< std::vector< double> > > weightT, Gradient;

	std::vector<std::vector<double> > dataInput, dataExpected;//data

	std::vector<std::string> palabras;
public:
	//Constructos
	net() {};
	net(std::vector<int> layersi, double alphaI, double momentumI, std::vector<int> actFunctionNI, double neuronWMi, int testItersi);

	//Matrix Operations
	std::vector< std::vector< std::vector< double> > > createMatrixVector(std::vector<int> sizes, double weightS);

	void resetWeightT();
	void resetNet();

	void addGradientT();

	std::vector<double> activate(std::vector<double> vals, int layerP);

	void setDataInfo(std::string dataFilesN);


	void run(std::vector<double> init);
	int train(double errV, int checkIterN, int breakIterN);
	void backpropagate(std::vector<double> eX);


	bool tryTest(double maxErr, int iteration);


	double getErr(int q);
	double getCErr();
	double getErrTest(std::vector<double> exOutput);

	double letMeTry(std::string testFileN);

};

#endif