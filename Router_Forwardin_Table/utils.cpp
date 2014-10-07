#include <string>
#include <iostream>
#include <sstream>
#include "utils.h"

using namespace std;

// for a given decimal as int between 0 and 255 returns a 8 bit vector
// converting decimal to binary
int* byteToBits(int byte) {
    
    int* bitArray = new int[8];
    for(int i=7; i>=0; i--) {
        bitArray[i] = byte%2;
        byte = byte/2;
    }
    
    return bitArray;
}


// constructor for Node class without arguments
Node::Node() {
    
    value = -1;
    isEnd = false;
    left = NULL;
    right = NULL;
    serial = -1;

}

// constructor for Node class with arguments as
// binary value to be stored in value and whether a node can be a end
Node::Node(int val, bool end) {

    value = val;
    // isEnd is true if a network address ends at that node (determined by subnet mask)
    isEnd = end;
    left = NULL;
    right = NULL;
    serial = -1;

}

// returns pointer to left node
Node* Node::getLeftPtr() {
    
    return left;

}

// returns pointer to right node
Node* Node::getRightPtr() {

    return right;

}

// sets pointer to left node
void Node::setLeftPtr(Node* node) {

    left = node;

}

// sets pointer to right node
void Node::setRightPtr(Node* node) {

    right = node;

}

// sets a node as a valid end to a network address
void Node::setEnd() {

    isEnd = true;

}

// stores index of the ip in vector in the node
void Node::setSerial(int sno) {

    serial = sno;

}

// returns whether a valid network part of ip address ends at that node
bool Node::getEnd() {

    return isEnd;

}

// returns index in ip address vector corresponding to ip address in trie
int Node::getSerial() {

    return serial;

}

// checks whether each the decimal no b/w two dots can be stored in a byte (0-255)
bool IPAddress::isValidNumber(int num) {

    if(num>=0 && num<=255)
        return true;
    return false;

}

// extracts each byte from ip address where each byte is separated by a dot
// also checks validity of ip address
bool IPAddress::extractIP() {
    
    // initializing each byte to 0
    quarter[0] = quarter[1] = quarter[2] = quarter[3] = 0;
    
    // checking whether all characters in ip are valid
    // string::npos is something like End of String
    // if there is an instance of inpermissible character some position rather than string::npos wil be returned
    if (ipstring.find_first_not_of("1234567890"+separator) != string::npos) {
        cout << "invalid character" << endl;
        return false;
    }
    
    stringstream stream;
    stream.str(ipstring);
    
    char dot1, dot2, dot3;
    
    // splitting the the string to components
    stream >> quarter[0] >> dot1 >> quarter[1] >> dot2 >> quarter[2] >> dot3 >> quarter[3];
    
    if (stream.eof() && !stream.fail()) {
        // checking if the separator is indeed the '.' (redundant check)
        if (dot1 == '.' && dot2 == '.' && dot3 == '.') {
            // checking if each byte is in range
            if(isValidNumber(quarter[0])&&isValidNumber(quarter[1])&&isValidNumber(quarter[2])&&isValidNumber(quarter[3])) {
                valid = true;
                return true;
            }
            else {
                cout << "invalid ip number" << endl;
                return false;
            }
        }
        else {
            cout << "invalid separator" << endl;
            return false;
        }
    }
    else {
        cout << "invalid data" << endl;
        return false;
    }

}

// prints the individual bytes extracted from ip address
void IPAddress::printDigits() {
    
    cout<<"Address in decimals: "<<quarter[0]<<" "<<quarter[1]<<" "<<quarter[2]<<" "<<quarter[3]<<endl;

}

// To debug: prints ip address in binary notation
void IPAddress::printBits() {
   
    cout<<"Address in bits: ";
    for(int i=0; i<4; i++) {
        int* bits = byteToBits(quarter[i]);
        for(int j=0; j<8; j++) {
            cout<<bits[j]<<" ";
        }
    }
    cout<<endl;
    cout<<"Bits in subnet: "<<getDecimalMask()<<endl;

}


// constructor for IPAddress
IPAddress::IPAddress(string ip) {

    separator = ".";
    valid = false;
    ipstring = ip;
    extractIP();
    // To debug: call to printDigits to check whether ip is being parsed properly
    // printDigits();

}

// get the ip address as array of 32 bits
int* IPAddress::getBits() {

    int* bitArray = new int[32];
    for(int i=0; i<4; i++) {
        int* eachByte = byteToBits(quarter[i]);
        for(int j=0; j<8; j++) {
            bitArray[8*i+j] = eachByte[j];
        }
    }
    return bitArray;

}

// extracts network part of address from ip address suing subnet mask
int IPAddress::getDecimalMask() {
    
    int num = 0;
    int* maskbits = getBits();
    for(int i=0; i<32; i++) {
        // since 1s in subnet mask are contiguos
        if(maskbits[i]!=1)
            break;
        num++;
    }
    return num;
    
}

// returns whether an ip address is valid or not
bool IPAddress::isValid() {

    return valid;

}

// returns ip address as a string
string IPAddress::getIPString() {

    return ipstring;

}

