#include "rFunctions.h"

int maximumIndex(std::vector<double> outVals){
    int indexi = 0;
    double maxVal = outVals[0];
    for(int i = 1; i < outVals.size();i++){
        if(outVals[i]>maxVal){
            maxVal = outVals[i];
            indexi = i;
        }
    }
    return indexi;
}