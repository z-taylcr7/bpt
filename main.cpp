#include <iostream>
#include "BPlusTree.hpp"
#include "String.hpp"
#include <algorithm>
using namespace Geneva;
String str("chao");
BPlusTree<50,50,250> Q("test");
void test(){
    String key=str;
    for(int i=1;i<=400;i++) {
        Q.insert(std::make_pair(str, i), i);
    }
    Q.show();
    for(int i=400;i>0;i-=2){
        Q.erase(std::make_pair(str,i));
    }
    Q.show();
    vector<long long>pat;
    Q.find(key,pat);
    if(pat.empty())std::cout<<"null";

    for(auto i=pat.begin();i!=pat.end();i++){
        std::cout<<*i<<' ';
    }
    std::cout<<std::endl;

}
void pour(){
    String ts("Tay");
    String jzm("Jiang");
    String diana("JiaRan");
    for(int i=1989;i<2000;i++)Q.insert(std::make_pair(ts,i),i);
    for(int i=19260817;i<19260831;i++)Q.insert(std::make_pair(jzm,i),i);
    for(int i=1;i<=520;i++)Q.insert(std::make_pair(diana,i),i);
}
void test2(){
    for(int i=1;i<=200;i++){
        Q.insert(std::make_pair(str,i),i);
    }

    for(int i=400;i>200;i--){
        Q.insert(std::make_pair(str,i),i);
    }
    String key=str;
    for(int i=199;i>0;i-=2){
        Q.erase(std::make_pair(str,i));
    }
    for(int i=201;i<400;i+=2){
        Q.erase(std::make_pair(str,i));
    }
    vector<long long>pat;
    Q.find(key,pat);
    if(pat.empty())std::cout<<"null";
    for(auto i=pat.begin();i!=pat.end();i++){
        std::cout<<*i<<' ';
    }
    std::cout<<std::endl;
}
int main() {
    int n;std::cin>>n;
    test2();

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
            for(auto i=pat.begin();i!=pat.end();i++){
                std::cout<<*i<<' ';
            }
            std::cout<<std::endl;
        }

    }

}
