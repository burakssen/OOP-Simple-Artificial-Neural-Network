/*
 *  Name:   Burak
 *  SurName:Şen
 *  Id:     150170063
 */


#ifndef SIGMOIDNEURON_H
#define SIGMOIDNEURON_H
#include "Neuron.h"
#include <cmath>
class SigmoidNeuron : public Neuron{
public:
    SigmoidNeuron():Neuron(){}
    SigmoidNeuron(double &value_z, double &activationV_a):Neuron(value_z,activationV_a){}
    void activate();
    void setValues(double);
    double getValue(){
        return this->activationV_a;
    }
    ~SigmoidNeuron(){}
};

void SigmoidNeuron::activate(){//in this function we calculate the activation value
    this->activationV_a = 1/(1 + exp(-this->value_z));
}

void SigmoidNeuron::setValues(double value_z) {// in this function we set the z value and activate the activation function
    this->value_z = value_z;
    this->activate();
}
#endif //SIGMOIDNEURON_H
