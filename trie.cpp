#include "trie.h"
#include "utils.h"
using namespace std;

// constructor for Trie
Trie::Trie() {

    root = new Node();

}


// inserts ip address, corresponding subnet mask
// and index in ip address vector of Router as a node in Trie
bool Trie::insert(IPAddress* ip, IPAddress* mask, int serial) {
    
    // get ip address as a 32-bit vector
    int* ipbits = ip->getBits();
    // get effective number of prefix bits that count for network part of
    // ip address in decimal form
    int maskNumber = mask->getDecimalMask();
    
    // start from root node (dummy node)
    Node* node = root;
    
    for(int i=0; i<maskNumber; i++) {
        // 0 stored to the left of tree
        if(ipbits[i]==0) {
            // initialize uninitialized nodes
            if(node->getLeftPtr()==NULL) {
                node->setLeftPtr(new Node(ipbits[i], false));
            }
            node = node->getLeftPtr();
        }
        // 1 stored to the right of tree
        else {
            // initialize uninitialized nodes
            if(node->getRightPtr()==NULL) {
                node->setRightPtr(new Node(ipbits[i], false));
            }
            node = node->getRightPtr();
        }
        
    }
    
    // we have covered a valid network part of ipaddress
    // as per the number of set bits in subnet mask
    node->setEnd();
    node->setSerial(serial);

    return true;

}

// find the longest network address that is prefix to queried ip address
int Trie::findIP(IPAddress* ip) {
    
    int* ipbits = ip->getBits();
    
    Node* node = root;
    
    // -1 is returned if no match found i.e. no network address in trie
    // is prefix to queried ip addres
    int serial = -1;
    
    for(int i=0; i<32; i++) {
        // move left for a 0
        if(ipbits[i]==0) {
            // no further matches can be found as continuity of matching bits broken
            if(node->getLeftPtr()==NULL) {
                break;
            }
            node = node->getLeftPtr();
        }
        // move right for a 1
        else {
            // no further matches can be found as continuity of matching bits broken
            if(node->getRightPtr()==NULL) {
                break;
            }
            node = node->getRightPtr();
        }
        // as we keep moving down the Trie, we keep track of index of ip address
        // that's longest prefix to queried ip address
        if(node->getEnd())
            serial = node->getSerial();
        
    }

    // returns index of longest network address in ipaddresses vector
    return serial;

}


