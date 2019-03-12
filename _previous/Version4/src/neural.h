#pragma once

#include "neuron.h"
#include <iostream>

class net{
    private:
        double alpha, neuronWM;
        int maxInp,actFunctionN, nLayers;
        std::vector<int> layers;

        std::vector<std::vector<double> > test,expected;
        std::vector<std::string> palabras;
        std::vector<std::vector<Neuron> > neurons;
    public:
        net(){};
        net(std::vector<int> layersi, double alphaI, int actFunctionNI, double neuronWMi);

        void setTestCases(std::string dataFilesN);
        
        void resetNet();
        void resetNetEasy();

        void run(std::vector<double> init);
        int train(double errV, int checkIterN, int breakIterN);
        void backpropagate(std::vector<double> eX);

        double getErr(int q);
        double getCErr();
        double getDerivate(double x, double y, int actFunctioni);

        int letMeTry(std::string testFileN, std::string wordFileN);
};

