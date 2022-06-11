//
// Created by Cristiano on 2022/6/11.
//

#ifndef BPLUSTREE_ZTEST_HPP
#define BPLUSTREE_ZTEST_HPP
namespace Geneva{
    void test(){
        BPlusTree<50,50,250> Q("test");
        String str("chao");
        String key=str;
        for(int i=1;i<=400;i++) {
            Q.insert(std::make_pair(str, i), i);
        }
        Q.show();
        for(int i=400;i>0;i-=2){
            Q.erase(std::make_pair(str,i));
        }
        Q.show();
        vector<std::pair<int,long long>>pat;
        Q.find(key,pat);
        if(pat.empty())std::cout<<"null";
        for(std::pair<int,long long> & i : pat){
            std::cout<<i.second<<' ';
        }
        std::cout<<std::endl;

    }
    void pour(){
        BPlusTree<50,50,250> Q("test");
        String ts("Tay");
        String jzm("Jiang");
        String diana("JiaRan");
        for(int i=1989;i<2000;i++)Q.insert(std::make_pair(ts,i),i);
        for(int i=19260817;i<19260831;i++)Q.insert(std::make_pair(jzm,i),i);
        for(int i=1;i<=520;i++)Q.insert(std::make_pair(diana,i),i);
    }
    void test2(){
        BPlusTree<50,50,250> Q("test");

        String str("chao");
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
        vector<std::pair<int,long long>>pat;
        Q.find(key,pat);
        if(pat.empty())std::cout<<"null";
        for(std::pair<int,long long> & i : pat){
            std::cout<<i.second<<' ';
        }
        std::cout<<std::endl;
    }
}
#endif //BPLUSTREE_ZTEST_HPP
