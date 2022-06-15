#include <iostream>
#include "HashBPlusTree.hpp"
#include "vector.hpp"
//#include "ztest.hpp"
#include <map>
#include <algorithm>
using namespace Geneva;
std::string t[1000];
std::string s[1000];
char c[10]={'r','o','s','e','n','a','m','u','l','v'};
char d[10]={'P','L','C','Y','K','Q','D','R','B','F'};
BPlusTree<>Q("test");
std::map<std::string,std::pair<int,long long>>R;
vector<std::pair<int, long long>> pat;
void init(){
    int cnt=0;
   std::string def="";
   for(int i=0;i<10;i++){
       for(int j=0;j<10;j++){
           for(int k=0;k<10;k++){s[cnt]=def+d[i]+d[j]+d[k];t[cnt++]=def+c[i]+c[j]+c[k];}
       }
   }

}
void test(){
    init();
    for(int i=0;i<1000;i++){
        for(int j=0;j<1000;j++){
            long long x=rand()%1926081719260817;
            int y=rand()%19260817;
            Q.insert(t[i]+s[j],x,y);
            R.insert(std::make_pair(t[i]+s[j], std::make_pair(y,x)));
        }
    }
    for(int i=0;i<1000;i++) {
        for (int j = 0; j < 1000; j++) {
            pat.clear();
            Q.find(t[i]+s[j], pat);
            if (pat.size() != 1) {
                Q.find(t[i]+s[j], pat);
                string key=t[i]+s[j];
                std::cout<<key<<':';
                if (pat.empty())std::cout << "null";
                for (std::pair<int, long long> &i: pat) {
                    std::cout << i.first << '|' << i.second << ' ';
                }
                std::cout << "wrong!\n";
            } else {
                std::pair<int, long long> tmp = R.find(t[i]+s[j])->second;
                if (pat[0] == tmp) {
                    std::cout << "bingo!\n";
                } else {
                    string key=t[i]+s[j];
                    std::cout<<key<<':';
                    std::cout << pat[0].first << '|' << pat[0].second << "-------" << tmp.first << '|' << tmp.second
                              << std::endl;
                }
            }
        }
    }


    }
int main() {
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
