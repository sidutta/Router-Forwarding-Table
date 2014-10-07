#include <string>
#include <iostream>
#include <vector>
using namespace std;

#ifndef UTILS_H
#define UTILS_H

int* byteToBits(int byte);

class Node {
    
    // stores bit 0 or 1 depending on bits of ip address
    int value;
    // stores index of network address ending at that node in the ip address
    // vector of the forwarding table
    int serial;
    // stores whether a valid network address ends at that node
    bool isEnd;
    // stores pointer to left node
    Node* left;
    // stores pointer to right node
    Node* right;

public:
    // constructor without arguments (not used anywhere though)
    Node();
    // constructor taking bit to be stored in node and whether its
    // an end to a valid network address
    Node(int val, bool end);
    // some getter functions
    Node* getLeftPtr();
    Node* getRightPtr();
    // returns whether a valid network address ends at that node
    bool getEnd();
    int getSerial();
    // some setter functions
    void setLeftPtr(Node* node);
    void setRightPtr(Node* node);
    void setEnd();
    void setSerial(int sno);
    
};

class IPAddress {
    
    // stores the ip address as a string as entered by the user
    string ipstring;
    // stores individual bytes of the ip address
    int quarter[4];
    // stores whether or not the ip address was deemed valid
    bool valid;
    // each byte is separated by a '.'
    string separator;
    // checks whether each the decimal no b/w two dots can be stored in a byte (0-255)
    bool isValidNumber(int num);
    bool extractIP();
    // prints the individual bytes extracted from ip address
    void printDigits();
    void printBits();
    
public:
    
    // constructor for IPAddress
    IPAddress(string ip);
    // get the ip address as array of 32 bits
    int* getBits();
    // returns number of continuos 1s in subnet address
    // to identify network part of ip address
    int getDecimalMask();
    // returns whether an ip address is valid or not
    bool isValid();
    // returns ip address as a string
    string getIPString();

};

#endif