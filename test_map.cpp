#include <map>
#include <iostream>
#include <typeinfo>

struct person{
    int id;
    std::string name;
};

struct node{
    int number;
    std::string name;
    std::vector<int> v;
    person p;
};

int main(){
    std::map<int,node> mp;
    // node n = mp[10];

//    std::cout<<n.number<<std::endl;

node n;
   std::cout<<n.p.name<<std::endl;

//    std::cout << "Type of a: " << typeid(n).name() << std::endl;
//    std::cout << "Type of a: " << typeid(n.name).name() << std::endl;

}