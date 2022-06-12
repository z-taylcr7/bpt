#include <iostream>
#include "BPlusTree.hpp"
#include "ztest.hpp"
//
#include <algorithm>
using namespace Geneva;
BPlusTree<50,50,250>Q("test");
void pour(){
    String ts("Tay");
    String jzm("Jiang");
    String diana("JiaRan");
    for(int i=1989;i<2000;i++)Q.insert(std::make_pair(ts,i),i);
    for(int i=19260817;i<19260831;i++)Q.insert(std::make_pair(jzm,i),i);
    for(int i=1;i<=520;i++)Q.insert(std::make_pair(diana,i),i);
}
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
