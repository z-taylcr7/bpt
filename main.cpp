#include <iostream>
#include "BPlusTree.hpp"
#include <algorithm>
using namespace Geneva;

int main() {
    BPlusTree<50,50,250> Q("test");
    int n;std::cin>>n;

    while(n--){
        std::string command;
        std::cin>>command;
        if(command=="insert"){
            String key;
            int value;
            std::cin>>key>>value;
            Q.insert(std::make_pair(key,value),1);
        }
        if(command=="delete"){
            String key;
            int value;
            std::cin>>key>>value;
            Q.erase(std::make_pair(key,value));
        }
        if(command=="find"){
            String key;
            std::cin>>key;
            vector<long long>pat;
            Q.find(key,pat);
            if(pat.empty())std::cout<<"null";
            for(long long & i : pat){
                std::cout<<i<<' ';
            }
            std::cout<<std::endl;
        }
    }

}
