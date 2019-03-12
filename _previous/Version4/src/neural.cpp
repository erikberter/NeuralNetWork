
#include "neuron.h"
#include "neural.h"
#include "actFunctions.h"
#include "rFunctions.h"
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iostream>

net::net(std::vector<int> layersi, double alphaI, int actFunctionNI, double neuronWMi){
    alpha = alphaI;
    actFunctionN = actFunctionNI;
    neuronWM = neuronWMi;
    layersi.push_back(0);
    //Create layers and neurons wrt nex layer
    //size but the output one
    for(int layerIHi  = 0; layerIHi < layersi.size()-2; layerIHi++){
        layers.push_back(layersi[layerIHi]);
        std::vector<Neuron> tempV;
        //The +1 implies bias
        for(int neuronLayerIHi = 0; neuronLayerIHi < layersi[layerIHi]+1;neuronLayerIHi++)
            tempV.push_back(Neuron(layersi[layerIHi+1],actFunctionN,neuronWM));
        neurons.push_back(tempV);
    }
    //Create Output Layer without bias
    //Output can't have relu so it will always have sigmoid rigth now
    layers.push_back(layersi[layersi.size()-2]);
    std::vector<Neuron> tempV;
    for(int neuronLayerOi = 0; neuronLayerOi < layersi[layersi.size()-2]+1;neuronLayerOi++)
            tempV.push_back(Neuron(layersi.back(),1,neuronWM));
    neurons.push_back(tempV);
    nLayers = layersi.size()-1;
}
void net::resetNet(){
    for(int i = 0; i < nLayers;i++)
        for(int k = 0; k < layers[i]+1;k++)
            neurons[i][k].fullReset(neuronWM);
}
void net::resetNetEasy(){
    for(int k = 0; k < nLayers;k++)
        for(int j = 0; j < layers[k]; j++)
            neurons[k][j].reset();
}
void net::run(std::vector<double> init){
    //First Layers
    for(int i = 0; i < layers[0]; i++){
        neurons[0][i].changeInput(init[i]);
        neurons[0][i].changeOutput(init[i]);
        for(int j = 0; j < layers[1]; j++)
            neurons[1][j].changeInput(init[i]*neurons[0][i].getWeight(j));
    }
    for(int i = 0; i < layers[1]; i++)
            neurons[1][i].changeInput(neurons[0][layers[0]].getWeight(i));
    
    //Hidden Layers
    for(int l = 1; l < nLayers-1;l++){
        for(int i = 0; i < layers[l]; i++)
            neurons[l][i].activate();
        for(int i = 0; i < layers[l]; i++){
            for(int j = 0; j < layers[l+1]; j++)
                neurons[l+1][j].changeInput(neurons[l][i].getOutput()*neurons[l][i].getWeight(j));
            
        }
        for(int i = 0; i < layers[l+1]; i++)
                neurons[l+1][i].changeInput(neurons[l][layers[l]].getWeight(i));
    }
    //Output Layer
    for(int i = 0; i < layers[nLayers-1]; i++)
        neurons[nLayers-1][i].activate();
}
double net::getDerivate(double x, double y, int actFunctioni){
    switch(actFunctioni){
        case 1:
            return logisticd(x,y);
            break;
        case 2:
            return relud(x,y);
            break;
        case 3:
            return swishd(x,y);
            break;
        default:
            return 0;
    }
    return 0;
}
void net::backpropagate(std::vector<double> eX){
    //Output layer
    for(int i = 0; i < layers[nLayers-1];i++){
        double delta = (neurons[nLayers-1][i].getOutput()-eX[i])*getDerivate(neurons[nLayers-1][i].getOutput(), neurons[nLayers-1][i].getInput(),neurons[nLayers-1][i].getActFunction());
        neurons[nLayers-1][i].setDelta(delta);
        for(int j = 0; j < layers[nLayers-2];j++)
            neurons[nLayers-2][j].setGradient(alpha*delta*neurons[nLayers-2][j].getOutput(),i);
    }
    //biases
    for(int i = 0; i < layers[nLayers-1];i++)
        neurons[nLayers-2][layers[nLayers-2]].changeWeight(alpha*(neurons[nLayers-1][i].getOutput()-eX[i])*getDerivate(neurons[nLayers-1][i].getOutput(), neurons[nLayers-1][i].getInput(),neurons[nLayers-1][i].getActFunction()),i);
    //Hidden Layer
    for(int i = nLayers-2 ; i > 0 ; i--){
        for(int j = 0; j < layers[i]; j++){
            double delta = 0;
            for(int z = 0; z < layers[i+1]; z++)
                delta+= neurons[i+1][z].getDelta()*neurons[i][j].getWeight(z);
            delta *= getDerivate(neurons[i][j].getOutput(), neurons[i][j].getInput(),neurons[i][j].getActFunction());
            neurons[i][j].setDelta(delta);
            for(int z = 0; z < layers[i-1]; z++)
                neurons[i-1][z].setGradient(alpha*delta*neurons[i-1][z].getOutput(),j);
        }
    }
    //Hidden Layer Bias
    for(int i = nLayers -2 ; i > 0 ; i--){
        for(int j = 0; j < layers[i]; j++){
            double delta = neurons[i][j].getDelta();
            neurons[i-1][layers[i-1]].changeWeight(alpha*delta,j);
        }
    }

    //Add gradients
    for(int i = 0; i < nLayers-1; i++)
        for(int j = 0; j < layers[i]; j++)
            neurons[i][j].addGradient();
}
void net::setTestCases(std::string dataFileN){
    std::string num;

    std::ifstream dataFile;
    dataFile.open("./trainingData/"+dataFileN);

    if(dataFile.is_open()){
        std::vector<double> c,f;
        //The following will loop for each entry of data
        while(dataFile >> num){
            c.push_back(stod(num));
            for(int dataInputi = 1; dataInputi < layers[0]; dataInputi++){
                dataFile >> num;
                c.push_back(stod(num));
            }
            for(int dataOutputi = 0; dataOutputi < layers[nLayers-1]; dataOutputi++){
                dataFile >> num;
                f.push_back(stod(num));
            }
            test.push_back(c);
            expected.push_back(f);
            c.clear();
            f.clear();
        }
    }
    maxInp = test.size();
    dataFile.close();
}
double net::getErr(int q){
    double err = 0.0;
    for(int i = 0; i < layers[nLayers-1];i++)
        err+=(expected[q][i]-neurons[nLayers-1][i].getOutput())*(expected[q][i]-neurons[nLayers-1][i].getOutput())/2;
    return err;
}
double net::getCErr(){
    double realErr = 0.0;
    for(int z = 0; z < maxInp; z++){ 
        run(test[z]);
        realErr+=getErr(z);
        resetNetEasy();
    }
    
    return realErr/maxInp;
}
int net::train(double errV, int checkIterN, int breakIterN){
    int q;
    unsigned int i;
    double actErr = 0.0;
    for(i = 1; i<breakIterN; i++){
        if(i%checkIterN==0){
            double cR = getCErr();
            std::cout << "El error despues de1 " << i << " iteraciones es de  : " << cR << std::endl;
            if(cR < errV) break;
        }
        q = rand() %maxInp;
        run(test[q]);
        backpropagate(expected[q]);
        resetNetEasy();
    }
    return i;
}
int net::letMeTry(std::string testFileN, std::string wordFileN){
    std::string num;
    std::ifstream testCaseFile, wordFile;
    std::vector<double> tempInput,outVals;
    int val, total = 0; 

    testCaseFile.open("./trainingData/"+testFileN);
    wordFile.open("./trainingData/"+wordFileN);

    if(testCaseFile.is_open() && wordFile.is_open()){
        while(testCaseFile >> num){
            tempInput.push_back(stod(num));
            for(int testCaseInputi = 1; testCaseInputi < layers[0]; testCaseInputi++){
                testCaseFile >> num;
                tempInput.push_back(stod(num));
            }
            wordFile >> num >> val;
            run(tempInput);

            for(int nOuti = 0; nOuti < layers[nLayers-1]; nOuti++)
                outVals.push_back(neurons[nLayers-1][nOuti].getOutput());
            int indexMax = maximumIndex(outVals);
            if(indexMax==val) total++;

            resetNetEasy();
            tempInput.clear();
            outVals.clear();
        }
    }
    testCaseFile.close();
    wordFile.close();
    
    return total;
}
