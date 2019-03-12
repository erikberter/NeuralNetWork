#include "mFuncts.h"
#include <cmath>

int maximumIndex(std::vector<double> outVals) {
	int indexi = 0;
	double maxVal = outVals[0];
	for (int i = 1; i < outVals.size(); i++) {
		if (outVals[i]>maxVal) {
			maxVal = outVals[i];
			indexi = i;
		}
	}
	return indexi;
}

std::vector<double> matrixProd(std::vector<double> vals, std::vector<std::vector<double> > weightM) {
	std::vector<double> tempVals(weightM[0].size(), 0.0);

	for (int i = 0; i < weightM.size(); i++) {
		for (int j = 0; j<weightM[0].size(); j++) {
			tempVals[j] += vals[i] * weightM[i][j];
		}
	}
	return tempVals;
}

double getDerivateV(double x, double y, int actFunctioni) {
	switch (actFunctioni) {
	case 1:
		return logisticd(x, y);
	case 2:
		return relud(x, y);
	case 3:
		return swishd(x, y);
	default:
		return 0;
	}
}



//Sigmoid Like Functions
double logistic(double x) {
	return 1.f / (1.f + exp(-x));
}
double logisticd(double x, double y) {
	return x*(1 - x);
}
double tanhP(double x) {
	return tanh(x);
}
double tanhd(double x, double y) {
	return 1 - x*x;
}

//Linear Rectifiers
double relu(double x) {
	return x*(x>0);
}
double relud(double x, double y) {
	return (y>0);
}

double leekyRelu(double x) {
	return x*(x>0) + 0.01*x*(x<0);
}
double leekyRelud(double x, double y) {
	return (y>0) + 0.01*(y<0);
}
//Others
double swish(double x) {
	return x / (1.f + exp(-x));
}
double swishd(double x, double y) {
	return x + y*x*(1 - x);
}