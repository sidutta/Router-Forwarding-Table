#include "trie.h"

using namespace std;

class Router {
    // number of ip(network) addresses in Router's forwarding table (not very helphul here)
    int count;
    // vector of ip(network) addresses in forwarding table
    vector<IPAddress*> ipaddresses;
    // vector of subnet masks (mask corresponding to ip has same index)
    vector<IPAddress*> subnetmasks;
    // trie (binary tree) to store ip addresses in table for fast search
    Trie* trie;
    
public:
    // Trie initialized in constructor
    Router() {
        trie = new Trie();
        count = 0;
    }
    
    // to add new ip(network) and corresponding subnet address to forwarding table
    bool addEntry(string ipaddress, string subnetmask) {
        
        IPAddress* ip = new IPAddress(ipaddress);
        IPAddress* mask = new IPAddress(subnetmask);
        // if ip address is not valid, execution will discontinue
        // boolean return value may help in determining if addition to forwarding table was successful
        if(!(ip->isValid())||!(mask->isValid())) {
            cout<<ip->getIPString()<<" "<<"Address is invalid\n";
            return false;
        }
        ipaddresses.push_back(ip);
        subnetmasks.push_back(mask);
        trie->insert(ip, mask, count);
        count++;
        return true;
        
    }
    
    // returns network and subnet address corresponding to queried ip address
    string* findEntry(string ipaddress) {
        
        IPAddress* ip = new IPAddress(ipaddress);
        int serial = -1;
        if(ip->isValid()) {
            // index of appropriate network address in vector returned from trie
            serial = trie->findIP(ip);
        }
        string* str = new string[2];
        if(serial!=-1) {
            str[0] = ipaddresses[serial]->getIPString();
            str[1] = subnetmasks[serial]->getIPString();
        }
        else {
            str[0] = "default";
        }
        return str;
        
    }
    
};

int main() {
    
    Router* router = new Router();
    
    string ipaddr, macaddr;
    
    // to read in the strings network address and subnet mask at top of input
    cin>>ipaddr>>macaddr;
    
    while(cin>>ipaddr) {
        if(ipaddr=="default")
            break;
        cin>>macaddr;
        router->addEntry(ipaddr, macaddr);
    }
    
    int testcases;
    cin>>testcases;
    while(testcases--) {
        string ipaddr;
        cin>>ipaddr;
        string* str = new string[2];
        str = router->findEntry(ipaddr);
        cout<<ipaddr<<" ";
        if(str[0]=="default")
            cout<<"default\n";
        else {
            cout<<str[0]<<" ";
            cout<<str[1]<<endl;
        }
    }
    
    return 0;
    
}
