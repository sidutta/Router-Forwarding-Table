#include "utils.h"
using namespace std;

#ifndef TRIE_H
#define TRIE_H

class Trie {

    Node* root;

public:

    Trie();
    bool insert(IPAddress* ip, IPAddress* mask, int serial);
    int findIP(IPAddress* ip);

};

#endif