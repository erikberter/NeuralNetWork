#pragma once

#include <vector>
#include <cmath>
class Neuron{
    private:
        int nextLayer, actFunction;
        double sumI, output,delta;
        std::vector<double> weight,gradient;
    public:
        Neuron(int nextLayerSize, int actFunctioni,double neuronWM);

        double getInput(){return sumI;};
        void changeInput(double val){ sumI+=val; };
        void changeOutput(double val){output = val;};
        
        void activate();
        int getActFunction(){return actFunction;};

        void fullReset(double neuronWM);

        void setGradient(double val, int pos){gradient[pos]=val;};

        void setDelta(double val){ delta = val;};
        double getDelta(){return delta;};

        double getWeight(int n){ return weight[n];};
        double getGradient(int n){ return gradient[n];};
        void changeWeight(double val,int n){weight[n]-=val;};
        double getOutput(){return output;};
        void addGradient();
        void reset();


};