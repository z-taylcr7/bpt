//
// Created by Cristiano on 2022/5/11.
//

#include <utility>

#ifndef BPLUSTREE_UTILITY_HPP
#define BPLUSTREE_UTILITY_HPP
namespace Geneva{
    template<class data>
    int upper_bound(data* st,data* ed,const data&key ){
        int mid,ans=0;
        int l=0,r=(ed-st);
        while(r-l>0){
            mid=((r+l)>>1);
            if(key<st[mid]){
                r=mid;
            }
            else ans=mid+1,l=mid+1;
        }
        return ans;
    }
    template<class data>
    int lower_bound(data* st,data* ed,const data&key ){
        int mid;
        int ans=0;
        int r=(ed-st);
        int l=0;
        while(r-l>0){
            mid=((r+l)>>1);
            if( st[mid]<key){
                ans=mid+1;
                l=mid+1;
            }
            else r=mid;
        }
        return ans;
    }

    template<class T1, class T2>
    class pair {
    public:
        T1 first;
        T2 second;
        constexpr pair() : first(), second() {}
        pair(const pair &other) = default;
        pair(pair &&other) = default;
        pair(const T1 &x, const T2 &y) : first(x), second(y) {}
        template<class U1, class U2>
        pair(U1 &&x, U2 &&y) : first(x), second(y) {}
        template<class U1, class U2>
        pair(const pair<U1, U2> &other) : first(other.first), second(other.second) {}
        template<class U1, class U2>
        pair(pair<U1, U2> &&other) : first(other.first), second(other.second) {}
    };

}
#ifndef SJTU_UTILITY_HPP
#define SJTU_UTILITY_HPP

#endif

#endif //BPLUSTREE_UTILITY_HPP
