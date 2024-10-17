#include <map>
#include <iostream>

int main(){
    std::map<int,int> mp;
    mp[19]=1;
    int x = mp[10];

   std::cout<<x<<std::endl;
}