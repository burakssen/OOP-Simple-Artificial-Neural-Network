/*
 *  Name:   Burak
 *  SurName:Şen
 *  Id:     150170063
 */


#ifndef NEURON_H
#define NEURON_H

class Neuron{// abstract base class
protected:
    double value_z; // z value of the neuron
    double activationV_a; // activation value of the a
public:
    Neuron(double value_z = 0.0,double activationV_a = 0.0){ // neuron constructor
        this->value_z = value_z; // we assign z value and activation value a
        this->activationV_a = activationV_a;
    }
    virtual void activate()=0; // pure virtual methods
    virtual void setValues(double)=0;
    virtual double getValue()=0;
    virtual ~Neuron()= default;
};
#endif //NEURON_H
