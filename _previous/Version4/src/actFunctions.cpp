#include <cmath>
#include "actFunctions.h"


//Sigmoid Like Functions
double logistic(double x){
    return 1.f/(1.f+exp(-x));
}
double logisticd(double x, double y){
    return x*(1-x);
}
double tanh(double x){
    return tanh(x);
}
double tanhd(double x, double y){
    return 1-x*x;
}

//Linear Rectifiers
double relu(double x){
    return x*(x>0);
}
double relud(double x, double y){
    return (y>0);
}

double leekyRelu(double x){
    return x*(x>0)+0.01*x*(x<0);
}
double leekyRelud(double x, double y){
    return (y>0)+0.01*(y<0);
}
//Others
double swish(double x){
    return x/(1.f+exp(-x));
}
double swishd(double x, double y){
    return x+y*x*(1-x);
}