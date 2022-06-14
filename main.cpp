#include <iostream>
#include "BPlusTree.hpp"
#include "vector.hpp"
//#include "ztest.hpp"

#include <algorithm>
using namespace Geneva;
BPlusTree<>Q("test");
void test(){
    string str("chaokawaii");
    string key=str;
    for(int i=1;i<=40;i++) {
        Q.insert(str,i, i);
    }
    Q.show();
    for(int i=40;i>0;i-=2){
        Q.remove(str,i);

    }
    Q.show();
    vector<std::pair<int,long long>>pat;
    Q.find(key,pat);
    if(pat.empty())std::cout<<"null";
    for(std::pair<int,long long> & i : pat){
        if(i.second%2==0)std::cout<<'\n';
        std::cout<<i.second<<' ';
    }
    std::cout<<'\n';

}

void show20(){
    string ts("Tay");
    for(int i=1;i<20;i++)Q.insert(ts,i,i);
    Q.show();
}
void test2(int x){
    string str("chao");
    string str2("chaochao");
    int max=x;
    for(int i=1;i<=2*max;i++){
        Q.insert(str,i,i);
    }
    for(int i=4*max;i>2*max;i--){
        Q.insert(str2,i,i);
    }
    string key=str;
    for(int i=2*max+1;i<4*max;i+=2){
        Q.remove(str2,i);
    }
    for(int i=2*max-1;i>0;i-=2){
        Q.remove(str,i);
    }

    vector<std::pair<int,long long>>pat;
    Q.find(key,pat);
    if(pat.empty())std::cout<<"null";
    for(std::pair<int,long long> & i : pat){
        if(i.first%2==1)std::cout<<i.first<<'\n';
    }
    key=str2;
    std::cout<<"pass"<<' '<<pat.size()<<'\n';
    pat.clear();
    Q.find(key,pat);
    if(pat.empty())std::cout<<"null";
    for(std::pair<int,long long> & i : pat){
        if(i.second%2==1)std::cout<<i.second<<'\n';
    }
    std::cout<<"pass"<<' '<<pat.size();
}
int main() {
    vector<std::pair<int, long long>> pat;
    int n;std::cin>>n;
        while(n--){
        std::string command;
        std::cin>>command;
        if(command=="show")Q.show();
        if(command=="insert"){
            string key;
            int value;
            std::cin>>key>>value;
            Q.insert(key,value,value);

        }
        if(command=="delete"){
            string key;
            int value;
            std::cin>>key>>value;
            Q.remove(key,value);
        }
        if(command=="find"){
            string key;
            std::cin>>key;
            pat.clear();
            Q.find(key,pat);
            if(pat.empty())std::cout<<"null";
            for(std::pair<int,long long> & i : pat){
                std::cout<<i.first<<' ';
            }
            std::cout<<'\n';
        }
        if(command=="quit")break;
    }
}
