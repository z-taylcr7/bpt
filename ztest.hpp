//
// Created by Cristiano on 2022/6/11.
//

#ifndef BPLUSTREE_ZTEST_HPP
#define BPLUSTREE_ZTEST_HPP
#include <vector>
namespace Geneva{
    void test(){
        String str("chaokawaii");
        String key=str;
        for(int i=1;i<=400;i++) {
            Q.insert(std::make_pair(str, i), i);
        }
        Q.show();
        for(int i=400;i>0;i-=2){
            Q.remove(std::make_pair(str,i));
        }
        Q.show();
        std::vector<std::pair<int,long long>>pat;
        Q.find(key,pat);
        if(pat.empty())std::cout<<"null";
        for(std::pair<int,long long> & i : pat){
            if(i.second%2==0)std::cout<<std::endl;
            std::cout<<i.second<<' ';
        }
        std::cout<<std::endl;

    }

    void show20(){
        String ts("Tay");
        for(int i=1;i<20;i++)Q.insert(std::make_pair(ts,i),i);
        Q.show();
    }
    void test2(int x){
        String str("chao");
        String str2("chaochao");
        int max=x;
        for(int i=1;i<=2*max;i++){
            Q.insert(std::make_pair(str,i),i);
        }
        for(int i=4*max;i>2*max;i--){
            Q.insert(std::make_pair(str2,i),i);
        }
        String key=str;
        for(int i=2*max-1;i>0;i-=2){
            Q.remove(std::make_pair(str,i));
        }
        for(int i=2*max+1;i<4*max;i+=2){

            Q.remove(std::make_pair(str2,i));

        }
        std::vector<std::pair<int,long long>>pat;
        Q.find(key,pat);
        if(pat.empty())std::cout<<"null";
        for(std::pair<int,long long> & i : pat){
            if(i.second%2==1)std::cout<<i.second<<std::endl;
        }
        key=str2;
        pat.clear();
        Q.find(key,pat);
        if(pat.empty())std::cout<<"null";
        for(std::pair<int,long long> & i : pat){
            if(i.second%2==1)std::cout<<i.second<<std::endl;
        }
        std::cout<<"end"<<' ';
    }
}
#endif //BPLUSTREE_ZTEST_HPP
