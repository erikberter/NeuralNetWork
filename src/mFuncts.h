#ifndef __MFUNCTS__H__
#define __MFUNCTS__H__
#include<vector>

//Index Type
int maximumIndex(std::vector<double> outVals);

//Matrix Operations
std::vector<double> matrixProd(std::vector<double> vals, std::vector<std::vector<double> > weightM);



//Linear Operations
double getDerivateV(double x, double y, int actFunctioni);



//Sigmoid Like fuctions
double logistic(double x);
double logisticd(double x, double y);
double tanhP(double x);
double tanhd(double x, double y);

//Linear Rectifier
double relu(double x);
double relud(double x, double y);
double leekyRelu(double x);
double leekyRelud(double x, double y);

//Special
double swish(double x);
double swishd(double x, double y);

#endif
