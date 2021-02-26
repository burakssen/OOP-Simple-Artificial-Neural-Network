/*
 *  Name:   Burak
 *  SurName:Şen
 *  Id:     150170063
 */


#ifndef NETWORKOPERATIONS_H
#define NETWORKOPERATIONS_H
#include "Network.h"
#include "SigmoidNeuron.h"
#include "ReluNeuron.h"
#include "LReluNeuron.h"
#include "Matrix.h"


class NetworkOperations{
    Network *network;
    Matrix<double> *w_matrix;
    Matrix<double> *b_vector;
    int *neuronNum;
    int layerNum;
    public:
        NetworkOperations(Network&);
        void addNetworkComponents(int,int*,int*,int*);
        void getValues();
        void calculateValues(int,int);
        void fill();
        void printActivationValues();
        ~NetworkOperations();
};

NetworkOperations::NetworkOperations(Network &network) { // network Operations constructor
    this->network = &network; // we assign network
    this->b_vector = NULL; // we assign b_vector and x_matrix to NULL
    this->w_matrix = NULL;
}


void NetworkOperations::addNetworkComponents(int layerNum, int *neuronNum, int *neuronType, int *inputValues) {
    //in this function we create the network with given inputs
    Layer *layer;
    layer = new Layer(); // we create a layer
    Layer *copyLayer; // we define a copylayer
    this->neuronNum = neuronNum; // we assign neuronNum and layerNum to reach them from other functions
    this->layerNum = layerNum;
    for(int i = 0; i < layerNum; i++){ // loop numberof layers
        copyLayer = new Layer(*layer); // we create new copyLayer from the layer
        for(int j = 0; j < *(neuronNum + i); j++){ //loop for these layers number of neurons
            if(i == 0){ // if i == 0 it is first layer in the first layer we just assign the input values
                if(*(neuronType + i) == 0){ //if neuron type is 0 our neuron SigmoidNeuron
                    SigmoidNeuron *sigmoidNeuron; // define a Sigmoid Neuron pointer
                    double temp = *(inputValues + j) *1.0; // for double numbers we multiply our input with 1.0
                    sigmoidNeuron = new SigmoidNeuron(temp,temp);//we create this neuron with the inputs
                    copyLayer->addNeuron(*sigmoidNeuron); // we add the neuron to copy layer
                }
                else if(*(neuronType + i) == 1){//if neuron type is 1 our neuron LReluNeuron
                    LReluNeuron *lReluNeuron;// define a LReluNeuron pointer
                    double temp = *(inputValues + j) *1.0;// for double numbers we multiply our input with 1.0
                    lReluNeuron = new LReluNeuron(temp,temp);//we create this neuron with the inputs
                    copyLayer->addNeuron(*lReluNeuron);// we add the neuron to copy layer
                }
                else if(*(neuronType + i) == 2){//if neuron type is 2 our neuron ReluNeuron
                    ReluNeuron *reluNeuron;// define a ReluNeuron pointer
                    double temp = *(inputValues + j) *1.0;// for double numbers we multiply our input with 1.0
                    reluNeuron = new ReluNeuron(temp,temp);//we create this neuron with the inputs
                    copyLayer->addNeuron(*reluNeuron);// we add the neuron to copy layer
                }
                else{//if neuron type is not one of them it is an error
                    delete copyLayer; // we delete created copylayer and layer to prevent memory leaks
                    delete layer;
                    string error = "Unidentified activation function!";
                    throw error; //we throw an error string
                }
            }
            else{ // if the layer is not the first layer
                if(*(neuronType + i) == 0){ //if neuron type is 0 our neuron SigmoidNeuron
                    SigmoidNeuron *sigmoidNeuron;
                    sigmoidNeuron = new SigmoidNeuron(); // we create the SigmoidNeuron without values
                    copyLayer->addNeuron(*sigmoidNeuron); // we add neuron to copylayer
                }
                else if(*(neuronType + i) == 1){//if neuron type is 1 our neuron LReluNeuron
                    LReluNeuron *lReluNeuron;
                    lReluNeuron = new LReluNeuron();// we create the LReluNeuron without values
                    copyLayer->addNeuron(*lReluNeuron);// we add neuron to copylayer
                }
                else if(*(neuronType + i) == 2){//if neuron type is 2 our neuron ReluNeuron
                    ReluNeuron *reluNeuron;
                    reluNeuron = new ReluNeuron();// we create the ReluNeuron without values
                    copyLayer->addNeuron(*reluNeuron);// we add neuron to copylayer
                }
                else{//if neuron type is not one of them error occurs
                    delete copyLayer; // we delete created copylayer and layer to prevent memory leaks
                    delete layer;
                    string error = "Unidentified activation function!";
                    throw error; // we throw an error string
                }
            }
        }
        this->network->addLayer(*copyLayer); // we add created copy layer to the network
    }
    delete layer; // and lastly we delete unused layer object
}


void NetworkOperations::getValues() { // in this function we start to calculate our neurons values
    for(int i = 0; i < layerNum-1; i++){ // loop layers one by one except last layer we don't have to create any matrices or vectors at the last layer
        this->w_matrix = new Matrix<double>(this->neuronNum[i],this->neuronNum[i+1]); //we create the w_matrix
        this->b_vector = new Matrix<double>(1,this->neuronNum[i+1]); // we create the b_vector
        this->fill();//we fill this w_matrix and b_vector with 0.1
        calculateValues(this->neuronNum[i+1],i); // we calculate and assign our values to each layers neurons
        delete this->w_matrix; // we delete used w_matrix and b_vector to create again and use again
        delete this->b_vector;
    }

}

void NetworkOperations::fill() { // in this function we fill w_metrix and b_matrix with 0.1
    *this->w_matrix <= 0.1; // I used <= operator overloading
    *this->b_vector <= 0.1;
}

void NetworkOperations::calculateValues(int neuronNum_2, int layerNum){
    //in this function we calculate each of the layers and assign the z values to the neurons
    NetworkNode* traverse;
    LayerNode* neuron;
    traverse = this->network->getHead(); // we get the network's head

    int j = 0;
    int k = 0;
    while(traverse){ // in this loop we determine which layer are we in
        if(k == layerNum){ // if k is equal to layerNum we break and in this layer we are in
            break;
        }
        k++; // if our layerNum is not equal we increase k value
        traverse = traverse->getNext(); // and we go to the next layer
    }
    neuron = traverse->getLayer()->getHead(); // we get the layer's head
    Matrix<double> temp(1,neuronNum_2); // we create a local matrix to get the results
    temp <= 0.0; // we fill it with 0.0
    while(neuron){ //in here we are doing matrix multiplication we multiply layer's neurons with matrix's values
        for(int i = 0; i < neuronNum_2; i++){
            temp.operator()(0,i) += neuron->getNeuron()->getValue() * this->w_matrix->operator()(j,i);
        }
        neuron = neuron->getNext();
        j++;
    }

    for(int i = 0; i < neuronNum_2 ; i++){ // and we add each neuron b_vector's values
        temp.operator()(0,i) +=  this->b_vector->operator()(0,i);
    }

    int i = 0;
    neuron = traverse->getNext()->getLayer()->getHead(); // we assign next layer's head to neuron
    while(neuron){ //and we loop the next neuron and assign calculated values
        neuron->getNeuron()->setValues(temp.operator()(0,i));
        neuron = neuron->getNext();
        i++;
    }
}

void NetworkOperations::printActivationValues() {// in this function we print out activation values
    this->network->printLayers();
}

NetworkOperations::~NetworkOperations() { // destructor of the network operations class
    delete this->network; // we delete network
}

#endif //NETWORKOPERATIONS_H
