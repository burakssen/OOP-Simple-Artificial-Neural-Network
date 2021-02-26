/*
 *  Name:   Burak
 *  SurName:Şen
 *  Id:     150170063
 */

#ifndef LEAKYNEURON_H
#define LEAKYNEURON_H

#include "Neuron.h"

class LReluNeuron:public Neuron{
    public:
        LReluNeuron():Neuron(){}
        LReluNeuron(double& value_z, double& activationV_a):Neuron(value_z,activationV_a){}
        void activate();
        void setValues(double);
        double getValue(){// get activation value
            return this->activationV_a;
        }
        ~LReluNeuron(){}
};
void LReluNeuron::activate(){ // activate the activation function and assign activation value
    this->activationV_a = max(0.1*this->value_z,this->value_z);
}

void LReluNeuron::setValues(double value_z) {
    this->value_z = value_z; //set the z value
    this->activate();//and invoke the activation function
}
#endif //LEAKYNEURON_H
