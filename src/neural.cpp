#include "mFuncts.h"
#include "neural.h"
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

net::net(std::vector<int> layersi, double alphaI,double momentumI,  std::vector<int> actFunctionNI, double neuronWMi, int testItersi) {
	//Set the initial values of the class
	alpha = alphaI;
	momentum = momentumI;
	neuronWM = neuronWMi;
	testIters = testItersi;
	layers = layersi;
	actFunctions = actFunctionNI;
	nLayers = layersi.size();

	//StartMatrixes
	layerVals = std::vector<std::vector<double> >();
	layerValsA = std::vector<std::vector<double> >();
	Deltas = std::vector<std::vector<double> >();
	for (int layerI = 0; layerI < nLayers; layerI++) {
		layerVals.push_back(std::vector<double>(layers[layerI], 0.0));
		layerValsA.push_back(std::vector<double>(layers[layerI]+1, 0.0));
		Deltas.push_back(std::vector<double>(layers[layerI]+1, 0.0));
	}
	weightT = createMatrixVector(layers, 0);
	Gradient =  createMatrixVector(layers, 0);
	resetWeightT();
}



//CREATION METHODS

//Creates a matrix with a extra length in each dimension for the bias.
std::vector< std::vector< std::vector< double> > > net::createMatrixVector(std::vector<int> sizes, double weightS) {
	std::vector< std::vector< std::vector< double> > > matrixT;
	for (int i = 0; i < sizes.size(); i++)
		matrixT.push_back(std::vector< std::vector< double> >(sizes[i] + 1, std::vector<double>(sizes[i+1], weightS*(double)(rand()/RAND_MAX))));
	return matrixT;
}

void net::resetWeightT() {
	for (int i = 0; i < layers.size() - 1; i++)
		for (int j = 0; j < layers[i] + 1; j++)
			for (int k = 0; k < layers[i + 1]; k++)
				weightT[i][j][k] = neuronWM*((double)rand() / (RAND_MAX));
}


void net::resetNet(){
	//This functions is redundant now, 
	// 	but we may need to add more stuff to it later,
	resetWeightT();
}

//MATRIX OPERATIONS

void net::addGradientT() {
	for (int i = 0; i < layers.size() - 1; i++)
		for (int j = 0; j < layers[i] + 1; j++)
			for (int k = 0; k < layers[i + 1]; k++)
				weightT[i][j][k] -= Gradient[i][j][k];
}

//VECTOR OPERATIONS

std::vector<double> net::activate(std::vector<double> vals, int layerP) {
	std::vector<double> tempVals(vals.size(), 1.0);
	switch (actFunctions[layerP]) {
	case 1:
		for (int i = 0; i < vals.size(); i++)
			tempVals[i] = logistic(vals[i]);
		break;
	case 2:
		for (int i = 0; i < vals.size() ; i++)
			tempVals[i] = relu(vals[i]);
		break;
	case 3:
		for (int i = 0; i < vals.size(); i++)
			tempVals[i] = swish(vals[i]);
		break;
	default:
		for (int i = 0; i < vals.size(); i++)
			tempVals[i] = 0;
	}
	tempVals.push_back(1.0); //Bias value
	return tempVals;
}


//NET OPERATIONS

void net::run(std::vector<double> init) {
	//First Layers
	layerVals[0] = init;
	init.push_back(1.0);//Add the bias
	layerValsA[0] = init;
	for (int i = 1; i < nLayers; i++) {
		layerVals[i] = matrixProd(layerValsA[i-1], weightT[i-1]);
		layerValsA[i] = activate(layerVals[i], i);
	}
}


void net::backpropagate(std::vector<double> eX) {
	//Output layer
	for (int i = 0; i < layers[nLayers - 1]; i++) {
		double delta = (layerValsA[nLayers - 1][i] - eX[i])*getDerivateV(layerValsA[nLayers - 1][i], layerVals[nLayers - 1][i], actFunctions[nLayers-1]); 
		Deltas[nLayers - 1][i] = delta;
		for (int j = 0; j < layers[nLayers - 2]; j++)
			Gradient[nLayers - 2][j][i] = -momentum*Gradient[nLayers - 2][j][i] +alpha*delta*layerValsA[nLayers - 2][j];
	}
	//Output Biases
	for (int i = 0; i < layers[nLayers - 1]; i++)
		Gradient[nLayers - 2][layers[nLayers - 2]][i] = -momentum*Gradient[nLayers - 2][layers[nLayers - 2]][i]+ alpha*(layerValsA[nLayers - 1][i] - eX[i])*getDerivateV(layerValsA[nLayers - 1][i], layerVals[nLayers - 1][i], actFunctions[nLayers-1]);
	//Hidden Layer
	for (int i = nLayers - 2; i > 0; i--) {
		for (int j = 0; j < layers[i]; j++) {
			double delta = 0;
			for (int z = 0; z < layers[i + 1]; z++)
				delta += Deltas[i + 1][z] * weightT[i][j][z];
			delta *= getDerivateV(layerValsA[i][j], layerVals[i][j], actFunctions[i]);
			Deltas[i][j] = delta;
			for (int z = 0; z < layers[i - 1]; z++)
				Gradient[i - 1][z][j] = -momentum*Gradient[i - 1][z][j]+ alpha*delta*layerValsA[i - 1][z];
		}
	}
	//Hidden Layer Bias
	for (int i = nLayers - 2; i > 0; i--)
		for (int j = 0; j < layers[i]; j++) 
			Gradient[i - 1][layers[i - 1]][j] = -momentum* Gradient[i - 1][layers[i - 1]][j] +alpha*Deltas[i][j];
	
	//Add gradients
	addGradientT();
}

//NET CONTROL

int net::train(double errV, int checkIterN, int breakIterN) {
	unsigned int i;
	for (i = 1; i<breakIterN; i++) {
		if (i%checkIterN == 0)
			if(tryTest(errV,i)) break;
		int q = rand() % maxInp;
		run(dataInput[q]);
		backpropagate(dataExpected[q]);
	}
	return i;
}


double net::letMeTry(std::string testFileN) {
	
	int val, total = 0;
	std::vector<std::vector<double> > testInput, testOutput;
	/*
	*	We will read the files and generate the two vectors
	*/
	//Test File reading ------------
	std::string fileTempS;

	
	std::ifstream testFile;
	testFile.open("./trainingData/test/" + testFileN);

	if (testFile.is_open()) {
		std::vector<double> tempDInput, tempDOutput;
		while (testFile >> fileTempS) {
			tempDInput.push_back(stod(fileTempS));
			for (int dataInputi = 1; dataInputi < layers[0]; dataInputi++) {
				testFile >> fileTempS;
				tempDInput.push_back(stod(fileTempS));
			}
			for (int dataOutputi = 0; dataOutputi < layers[nLayers - 1]; dataOutputi++) {
				testFile >> fileTempS;
				tempDOutput.push_back(stod(fileTempS));
			}
			testInput.push_back(tempDInput);
			testOutput.push_back(tempDOutput);
			tempDInput.clear();
			tempDOutput.clear();
		}
	}
	int testMaxInp = testInput.size();
	testFile.close();

	//--------------------------------
	double errT=0;
	for(int i = 0; i < testMaxInp; i++){
		run(testInput[i]);
		errT += getErrTest(testOutput[i]);
	}
	return errT;
}


//ERROR HANDLING

bool net::tryTest(double maxErr, int iteration){
	double cR = getCErr();

	std::cout << "El error despues de1 " << iteration << " iteraciones es de  : " << cR << std::endl;

	if(cR > maxErr) return false;
	else return true;
}

double net::getErr(int q) {
	double err = 0.0;
	for (int i = 0; i < layers[nLayers - 1]; i++)
		err += (dataExpected[q][i] - layerValsA[nLayers - 1][i])*(dataExpected[q][i] - layerValsA[nLayers - 1][i]) / 2;
	return err;
}
double net::getCErr() {
	double realErr = 0.0;
	for (unsigned int z = 0; z < maxInp; z++) {
		run(dataInput[z]);
		realErr += getErr(z);
	}

	return realErr / maxInp;
}


double net::getErrTest(std::vector<double> exOutput){
	double err = 0.0;
	for (int i = 0; i < layers[nLayers - 1]; i++)
		err += (exOutput[i] - layerValsA[nLayers - 1][i])*(exOutput[i] - layerValsA[nLayers - 1][i]) / 2;
	return err;
}

//DATA HANDLING

void net::setDataInfo(std::string dataFileN) {
	std::string fileTempS;

	//Data Files Reading
	std::ifstream dataFile;
	dataFile.open("./data/trainingData/" + dataFileN);

	if (dataFile.is_open()) {
		std::vector<double> tempDInput, tempDOutput;
		//The following will loop for each entry of data
		while (dataFile >> fileTempS) {
			tempDInput.push_back(stod(fileTempS));
			for (int dataInputi = 1; dataInputi < layers[0]; dataInputi++) {
				dataFile >> fileTempS;
				tempDInput.push_back(stod(fileTempS));
			}
			for (int dataOutputi = 0; dataOutputi < layers[nLayers - 1]; dataOutputi++) {
				dataFile >> fileTempS;
				tempDOutput.push_back(stod(fileTempS));
			}
			dataInput.push_back(tempDInput);
			dataExpected.push_back(tempDOutput);
			tempDInput.clear();
			tempDOutput.clear();
		}
	}
	maxInp = dataInput.size();
	dataFile.close();

}


