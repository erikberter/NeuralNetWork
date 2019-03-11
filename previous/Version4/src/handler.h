#pragma once

#include <vector>
#include <string>
#include "neural.h"


class netHandler{

    private:
        net nNet;

        std::string configFileN;

        std::vector<int> scheme; //layers 
        std::vector<std::string> testFilesN, wordFilesN, resultNames;
        std::string dataFileN, resultFileN;
        std::string temp;
        double maxErr, alpha,neuronWM;
        int breakIterN, checkIterN;
        int actFunction, nIter, nLayers, nTestFiles;
    public:
        netHandler();
        netHandler(std::string configFileNI);
        int readConfig();
        int createNet();
        int setTestCases();
        int startCycle();

        void coutConfig();

};