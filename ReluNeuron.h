/*
 *  Name:   Burak
 *  SurName:Şen
 *  Id:     150170063
 */


#ifndef RELUNEURON_H
#define RELUNEURON_H
#include "Neuron.h"

class ReluNeuron: public Neuron{
public:
    ReluNeuron():Neuron(){}
    ReluNeuron(double &value_z, double &activationV_a):Neuron(value_z,activationV_a){} //constructor
    void activate(); // virtual methods
    void setValues(double);
    double getValue(){
        return this->activationV_a;
    }
    ~ReluNeuron(){}
};

void ReluNeuron::activate(){ //in this function we calculate the activation value
    this->activationV_a = max(0.0,this->value_z);
}

void ReluNeuron::setValues(double value_z) { // in this function we set the z value and activate the activation function
    this->value_z = value_z;
    this->activate();
}
#endif //RELUNEURON_H
