#include "handler.h"
#include "neural.h"
#include "handler.h"

#include <fstream>
#include <string>

netHandler::netHandler(){
    configFileN="config";
    //default Options
    breakIterN = 10000000;
    checkIterN = 1000;
}


netHandler::netHandler(std::string configFileNI){
    configFileN = configFileNI;
    //Default Options
    breakIterN = 10000000;
    checkIterN = 1000;
}

int netHandler::readConfig(){
    std::ifstream configFile;
    configFile.open("./"+configFileN);
    if(configFile.is_open()){
        std::string tempCS;
        while(configFile >> tempCS){
            if(tempCS=="net"){
                configFile >> tempCS;
                nLayers = std::stoi(tempCS);
                for(unsigned int tempIFF = 0; tempIFF < nLayers; tempIFF++){
                    configFile >> tempCS; 
                    scheme.push_back(std::stoi(tempCS));
                }
            }
            else if(tempCS== "nTestFiles"){configFile >> tempCS; nTestFiles = std::stoi(tempCS);}
            else if(tempCS== "maxErr"){configFile >> tempCS; maxErr = std::stod(tempCS);}
            else if(tempCS== "alpha"){configFile >> tempCS; alpha = std::stod(tempCS);}
            else if(tempCS== "neuronWM"){configFile >> tempCS; neuronWM = std::stod(tempCS);}
            else if(tempCS== "actFunction"){configFile >> tempCS; actFunction = std::stoi(tempCS);}
            else if(tempCS== "checkIterN"){configFile >> tempCS; checkIterN = std::stoi(tempCS);}
            else if(tempCS== "breakIterN"){configFile >> tempCS; breakIterN = std::stoi(tempCS);}
            else if(tempCS== "dataFile") configFile >> dataFileN;
            else if(tempCS== "testFile"){
                for(int nTestFilesi = 0; nTestFilesi < nTestFiles; nTestFilesi++){
                    std::string tempFileName;
                    configFile >> tempFileName;
                    testFilesN.push_back(tempFileName);
                }
            }
            else if(tempCS== "wordFile"){
                for(int nTestFilesi = 0; nTestFilesi < nTestFiles; nTestFilesi++){
                    std::string tempFileName;
                    configFile >> tempFileName;
                    wordFilesN.push_back(tempFileName);
                }
            }
            else if(tempCS== "iterN"){configFile >> tempCS; nIter = std::stoi(tempCS);}
            else if(tempCS== "resultFile") configFile >> resultFileN;
            else if(tempCS=="names"){
                for(int nTestFilesi = 0; nTestFilesi < nTestFiles; nTestFilesi++){
                    std::string tempFileName;
                    configFile >> tempFileName;
                    resultNames.push_back(tempFileName);
                }
            }
            else return 1;
        }
    }
    configFile.close();
    return 0;
}

int netHandler::createNet(){
    nNet = net(scheme, alpha , actFunction, neuronWM);
    return 0;
}

int netHandler::setTestCases(){
    nNet.setTestCases(dataFileN);
    return 0;
}

int netHandler::startCycle(){
    int iter=0, testA = 0;
    std::vector<int> totalTestV(nTestFiles,0);
    std::cout << "Empezamos illo" << std::endl;
    for(int i = 0; i < nIter; i++){
        iter+= nNet.train(maxErr,checkIterN,breakIterN);
        std::cout << "Hemos salido del Train" << std::endl;
        for(int nTestFilesi = 0; nTestFilesi < nTestFiles; nTestFilesi++ ){
            totalTestV[nTestFilesi]+= nNet.letMeTry(testFilesN[nTestFilesi],wordFilesN[nTestFilesi]); 
        }
        
        nNet.resetNet();
    }
    std::cout << "Terminamos illo" << std::endl;
    std::string schemeS = "";
    for(int i = 0; i < nLayers-1; i++){
        schemeS+=std::to_string(scheme[i])+"->";
    }
    schemeS+=std::to_string(scheme[nLayers-1]);
    
    for(int nTestFilesi = 0; nTestFilesi < nTestFiles; nTestFilesi++){
        std::ofstream outfile;
        outfile.open("./results/"+resultFileN, std::ios_base::app);
        std::cout << "Grabando el file " << resultNames[nTestFilesi] << std::endl;
        
        std::string line = "";
        line+=resultNames[nTestFilesi]+"::";
        line+=schemeS+"::";
        line+=std::to_string((int)(iter/nIter))+"::";
        line+=std::to_string(totalTestV[nTestFilesi])+"\n";
        outfile << line;
        outfile.close();
        
    }
    return 0;
}
    
void netHandler::coutConfig(){

    std::cout << "The config is the Following" << std::endl;
    std::cout << "configFileN:" << configFileN << std::endl;
    std::cout << "dataFileN:" << dataFileN << std::endl;
    std::cout << "resultFileN:" << resultFileN << std::endl;
    std::cout << "maxErr:" << maxErr << std::endl;
    std::cout << "alpha:" << alpha << std::endl;
    std::cout << "actFunction:" << actFunction << std::endl;
    std::cout << "nIter:" << nIter << std::endl;
    std::cout << "nLayers:" << nLayers << std::endl;

    for(int i = 0; i < nLayers-1; i++){
        std::cout << scheme[i] << "->";
    } 
    std::cout << scheme[nLayers-1] << std::endl;

}