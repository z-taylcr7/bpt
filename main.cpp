#include <iostream>
#include "BPlusTree.hpp"
#include "ztest.hpp"
//
#include <algorithm>
using namespace Geneva;
BPlusTree<50,50,250>Q("test");

int main() {
    int n;std::cin>>n;
    while(n--){
        std::string command;
        std::cin>>command;
        if(command=="show")Q.show();
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
            std::vector<std::pair<int,long long>>pat;
            Q.find(key,pat);
            if(pat.empty())std::cout<<"null";
            for(std::pair<int,long long> & i : pat){
                std::cout<<i.second<<' ';
            }
            std::cout<<std::endl;
        }
    }

}
