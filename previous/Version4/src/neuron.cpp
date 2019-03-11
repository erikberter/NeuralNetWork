#include "neuron.h"
#include "actFunctions.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

Neuron::Neuron(int nextLayerSize, int actFunctioni, double neuronWM){
    nextLayer = nextLayerSize;
    actFunction = actFunctioni;
    sumI=output=delta=0.0;
    for(int i = 0; i < nextLayerSize; i++){
        double z = neuronWM*((double) rand() / (RAND_MAX));
        weight.push_back(z);
        gradient.push_back(0.0);
    }
}


void Neuron::addGradient(){
    for(int i = 0; i < nextLayer; i++){
        weight[i]-=gradient[i];
    }
}
void Neuron::reset(){
    sumI=output=delta=0.0;
}

void Neuron::fullReset(double neuronWM){
    sumI=output=delta=0.0;
    weight.clear();
    gradient.clear();
    for(int i = 0; i < nextLayer; i++){
        double z = neuronWM*((double) rand() / (RAND_MAX));
        weight.push_back(z);
        gradient.push_back(0.0);
    }
}
 void Neuron::activate(){ 
     switch(actFunction){
         case 1:
            output = logistic(sumI);
            break;
         case 2:
            output = relu(sumI); 
            break;
         case 3:
            output = swish(sumI);
            break;
         default:
            output = 0.0;
     }
     
}