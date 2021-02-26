/*
 *  Name:   Burak
 *  SurName:Şen
 *  Id:     150170063
 */


#ifndef LAYER_H
#define LAYER_H

#include "Neuron.h" // we include Neuron header to store neurons in the layernode

class LayerNode{
    Neuron *neuron;
    LayerNode *next;
    public:
        LayerNode(Neuron&);
        LayerNode* getNext();
        void setNext(LayerNode*);
        Neuron* getNeuron();
        ~LayerNode();
};

LayerNode::LayerNode(Neuron& neuron) { // layerNode constructor we assign neuron
    this->neuron = &neuron;
    this->next = NULL;
}

LayerNode* LayerNode::getNext() { // return layerNode next
    return this->next;
}

Neuron* LayerNode::getNeuron(){ // return layerNode's neuron
    return this->neuron;
}

void LayerNode::setNext(LayerNode *next) {  // set next of the layerNode
    this->next = next;
}

LayerNode::~LayerNode() {//layerNode destructor we delete allocated neuron
    delete this->neuron;
}

class Layer{
    LayerNode* layerHead;
    public:
        Layer();
        Layer(const Layer&);
        void addNeuron(Neuron&);
        void printNeurons();
        LayerNode* getHead();
        ~Layer();
        void deleteAllLayers(LayerNode&);
};

Layer::Layer() { // layer constructor
    this->layerHead = NULL; //we assign head of the layer NULL
}

Layer::Layer(const Layer &newLayer){ //copy constructor of the layer
    this->layerHead = newLayer.layerHead;// we just set the head
}

void Layer::addNeuron(Neuron& newNeuron) {// we add neurons to the layer
    LayerNode *traverse;
    LayerNode *newNode;
    newNode = new LayerNode(newNeuron); // we create new layernode
    if(this->layerHead == NULL){// if head is null
        this->layerHead = newNode;// we add our newnode to the layers head
        this->layerHead->setNext(NULL); // we set head's next to the NULL
        return; // after the setting next we return
    }
    traverse = this->layerHead; // if head is not NULL we assign head to traverse
    while(traverse->getNext()){ // while traverse has a next
        traverse = traverse->getNext(); // we go to the end of the list
    }
    newNode->setNext(NULL); // we set the next of the node to NULL
    traverse->setNext(newNode); // we set the next of the traverse to newnode
}

void Layer::printNeurons() { // in this function we print all of the layers
    LayerNode *traverse;
    traverse = this->layerHead; // we assign layer's head to layernode
    while(traverse){ // while there is a node
        cout<<traverse->getNeuron()->getValue()<<endl; // we print the neuron information
        traverse = traverse->getNext(); // we go to next neuron
    }
}

LayerNode* Layer::getHead() { //we get head of the layer
    return this->layerHead;
}

void Layer::deleteAllLayers(LayerNode &node) { // when destructor is invoked we call this recursive function
    if(node.getNext()){//if there is a next node
        deleteAllLayers(*node.getNext());//we go to the next node
    }
    delete &node; // if there is not any next node we delete the node
}

Layer::~Layer() {//destructor of the layer
    if(this->layerHead != NULL){//if layer head is not NULL
        deleteAllLayers(*this->layerHead); // we start to delete all of the layer
    }
}

#endif //LAYER_H
