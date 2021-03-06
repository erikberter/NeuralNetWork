#include <iostream>
#include <ctime>
#include <random>
#include <vector>

#include "handler.h"
using namespace std;

int main(){

    srand(time(NULL));
    int errA=0;
    netHandler netH("config");
    errA = netH.readConfig();
    if(errA==0) cout << "It could read config";
    else cout << "It couldnt read config"; 
    cout << endl;
    errA = netH.createNet();
    if(errA==0) cout << "It could create net";
    else cout << "It couldnt create net"; 
    cout << endl;
    errA = netH.setTestCases();
    if(errA==0) cout << "It could set Testcases";
    else cout << "It couldnt set TestCases"; 
    cout << endl;
    netH.coutConfig();
    errA = netH.startCycle();
    if(errA==0) cout << "It could cycle";
    else cout << "It couldnt cycle"; 
    cout << endl;
    return 0;
}