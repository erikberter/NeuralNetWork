#pragma once


//Sigmoid Like fuctions
double logistic(double x);
double logisticd(double x, double y);
double tanh(double x);
double tanhd(double x, double y);

//Linear Rectifier
double relu(double x);
double relud(double x, double y);
double leekyRelu(double x);
double leekyRelud(double x, double y);

//Special
double swish(double x);
double swishd(double x, double y);