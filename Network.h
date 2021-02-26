/*
 *  Name:   Burak
 *  SurName:Şen
 *  Id:     150170063
 */


#ifndef NETWORK_H
#define NETWORK_H

#include "Layer.h"

class NetworkNode{
    Layer *layer;
    NetworkNode *next;
    public:
        NetworkNode(Layer&);
        void setNext(NetworkNode*);
        NetworkNode* getNext();
        Layer* getLayer();
        ~NetworkNode();
};

NetworkNode::NetworkNode(Layer& layer) { //NetworkNode constructor
    this->layer = &layer; //we assign a layer
    this->next = NULL; //we assign the next of the node
}

void NetworkNode::setNext(NetworkNode *next) { //set next
    this->next = next;
}

NetworkNode* NetworkNode::getNext() { //get next
    return this->next;
}

Layer* NetworkNode::getLayer() { //get layer
    return this->layer;
}

NetworkNode::~NetworkNode() { // networkNode destructor
    delete this->layer; // delete the layer
}

class Network{
    NetworkNode *networkHead;
    public:
        Network();
        void addLayer(Layer&);
        void printLayers();
        NetworkNode* getHead();
        ~Network();
        void deleteAllLayers(NetworkNode&);
};

Network::Network() { // network constructor
    this->networkHead = NULL; // assign head to NULL
}

void Network::addLayer(Layer& layer) { // in this function we add layer to the network
    NetworkNode *traverse;
    NetworkNode *newNode;
    newNode = new NetworkNode(layer); // we create a new network node with given layer
    if(this->networkHead == NULL){ // if network head is NULL
        this->networkHead = newNode; // we add newnode to network head
        this->networkHead->setNext(NULL); // and we set the next of it NULL
        return;//then return
    }
    traverse = this->networkHead;// we assign traverse to network head
    while(traverse->getNext()){ // if traverse has any next
        traverse = traverse->getNext(); // we go to the end of the list
    }
    newNode->setNext(NULL); // we set the next of the newnode to NULL
    traverse->setNext(newNode); // we set the next of the traverse to newnode
}

void Network::printLayers() { //in this function we print all of the layers one by one
    NetworkNode* traverse;
    traverse = this->networkHead;
    int i = 0;
    while(traverse){// while traverse exist we print layers one by one
        cout<<"Layer: "<<i<<endl;
        traverse->getLayer()->printNeurons(); // we print neurons one by one
        traverse = traverse->getNext(); // we go to next layer
        i++; //increase index of the layer
    }
}

NetworkNode* Network::getHead() { // get network head
    return this->networkHead;
}

void Network::deleteAllLayers(NetworkNode &node) { // in this recursive function we delete all layers
    if(node.getNext()){ // if node has a next
        deleteAllLayers(*node.getNext()); // we go to that next
    }
    delete &node;//if there is not we delete the node
}

Network::~Network(){ // network destructor
    if(this->networkHead != NULL){
        deleteAllLayers(*this->networkHead); // if there is a network head we invoke recursive function and delete the list
    }
}

#endif //NETWORK_H
