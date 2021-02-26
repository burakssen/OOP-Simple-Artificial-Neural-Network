/*
 *  Name:   Burak
 *  SurName:Şen
 *  Id:     150170063
 */

#ifndef FILEOPERATION_H
#define FILEOPERATION_H
#include <fstream>

int returnArrayLength(string); //prototype of the function returnArrayLength

class FileOperation{
    int layerNum;
    int *neuronNum;
    int *neuronType;
    int *inputValues;
    string layerNumStr;
    string neuronNumStr;
    string neuronTypeStr;
    string inputValuesStr;
    public:
        FileOperation();
        void openFile(string);
        void getValues();
        void print();
        int *returnArray(string);
        int getLayerNum();
        int *getNeuronNum();
        int *getNeuronType();
        int *getInputValues();
        ~FileOperation();
};

FileOperation::FileOperation() {//file Operations constructor
    this->inputValues = NULL;
    this->neuronType = NULL;
    this->neuronNum = NULL;
}
void FileOperation::openFile(string fileName) { //int this function we get our values to string variables from given file
    ifstream fileInput; //we create a fileInput fstream object
    if(!fileInput.is_open()){ // we open the file if it is not open
        fileInput.open(fileName);
    }
    getline(fileInput,this->layerNumStr,'\n'); //we get the lines one by one and we return the values to the string variables
    getline(fileInput,this->neuronNumStr,'\n');
    getline(fileInput,this->neuronTypeStr,'\n');
    getline(fileInput,this->inputValuesStr,'\n');
    fileInput.close(); // when we get the lines we close the file
    this->getValues(); // and we initialize the strings to integers in the getValues function
}

void FileOperation::getValues() {   //int this function ve return our strings to proper integer forms (int pointer array or int)
    this->layerNum = atoi(this->layerNumStr.c_str()); // we assign the layerNum string to int
    this->neuronNum = returnArray(this->neuronNumStr);  // we get the integer arrays from the return ArrayFunction
    this->neuronType = returnArray(this->neuronTypeStr);
    this->inputValues = returnArray(this->inputValuesStr);
    if(this->neuronNum[0] != returnArrayLength(this->inputValuesStr)){ // we determine if length of the inputvalues is equal or not to the number of neurons of the first layer
        string error = "Input shape does not match!"; //if not equal we throw an error
        throw error;
    }
}

int* FileOperation::returnArray(string str) {   // we return the arrays
    int *temp;
    temp = (int*)malloc(sizeof(int)*returnArrayLength(str)); // we create local array with malloc with given string's size
    string tempStr = str;//we assign our string to a local string variable
    int j = 0;
    for(string::iterator it=tempStr.begin(); it!=tempStr.end(); ++it){ // our iterator starts from the first character of the string
        if(*it != ' '){// if our iterator's value is not space          // and we went until the last character
            if(*it == '-'){//and if our iterator's value is negative    it -> -2
                it++;//we increase the iterator index and      it -> 2
                *(temp + j) = -(*it -'0'); //we assign the negative of the number to the array
            }else {// if it is positive
                *(temp + j) = *it - '0';// we assign the value to to the array
            }
            j++; // we increase the array index if it is iterator's value is not a space
        }
    }
    return temp; // we return the integer temp array
}

int returnArrayLength(string str){ //we return the length of the array
    int temp = 0;
    for(int i = 0; i < signed(str.length()); i++){ // we loop to the end of the string str.length() is return an unsigned number we change it to a signed number
        if(str[i] == '-'){ // if our number is a negatif number we skip that "-" character
            i+=1;
        }
        if(str[i] != ' '){ // if our character is not a space
            temp += 1; // we increate the counter
        }
    }
    return temp; //return the counter temp
}

int FileOperation::getLayerNum() { // we return the layerNum
    return this->layerNum;
}

int* FileOperation::getNeuronNum() { // we return the neuronNum
    return this->neuronNum;
}

int* FileOperation::getNeuronType() { // we return the neuronType
    return this->neuronType;
}

int* FileOperation::getInputValues() { // we return the input values
    return this->inputValues;
}

FileOperation::~FileOperation() { // destructor of the fileOperations we free the allocated values of the arrays
    free(this->neuronNum);
    free(this->neuronType);
    free(this->inputValues);
}

#endif //FILEOPERATION_H
