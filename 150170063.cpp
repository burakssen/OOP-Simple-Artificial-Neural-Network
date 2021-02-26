/*
 *  Name:   Burak
 *  SurName:Şen
 *  Id:     150170063
 */

#include <iostream>

using namespace std;
#include "Network.h"            //for creating a network we include network header
#include "FileOperation.h"      //for getting datas from files we include fileoperation header
#include "NetworkOperations.h"  //for doing network operations we include network operations header

int main(int argc, char *argv[]) {   //for getting files from command line we place the main function arguments
    string fileName = argv[1]; // we get filename from command line
    FileOperation file; // we create the file object from file operations it contains layerNum, neuronNum, neuronType, inputValues
    try { // we declare a try catch unit if in openFile function of the file has any error
        file.openFile(fileName); //we get the values from the input file and we saved them in the file object
    }
    catch(const string& error){ //if any error we catch the thrown string
        cerr<<error; //we print the error string
        return 1;   //and we terminate the program with error code 1
    }
    Network *network; //we define a network pointer
    network = new Network(); // we create a new network
    NetworkOperations *networkOperations; // we define a network operations pointer
    networkOperations = new NetworkOperations(*network); // we create a new network operations object
    int layerNum = file.getLayerNum(); // we get datas from the file
    int *neuronNum = file.getNeuronNum();
    int *neuronType = file.getNeuronType();
    int *inputValues = file.getInputValues();
    try{// we declare a try catch unit if in addNetworkComponents function of the networkOperation object has any error
        networkOperations->addNetworkComponents(layerNum,neuronNum,neuronType,inputValues); //we create our structre of the network with given values
    }
    catch(const string& error){ // if there is any thrown errors we catch them and we print them
        cerr<<error;
        delete networkOperations; // because we create the networkOperation object we have to delete it before the termination
        return 1;//we terminate the program with error code 1,   //network object deleted in the networkOperations because it was passed by referance
    }
    networkOperations->getValues(); // we activate the neural network and calculate our neurons z values and activated values
    networkOperations->printActivationValues(); // we print all of layer with their neurons activation values

    delete networkOperations; //we delete the networkOperations object network object will deleted in the networkOperations object's destructor

    return 0;
}
