#include "include/external/nlohmann.hpp"
#include <iostream>
#include <string>

struct Outer{
    std::string inner;
};

inline void to_json(nlohmann::json &j, const Outer &o){
    j = nlohmann::json{
        {"inner", o.inner},
    };
}


inline void from_json(const nlohmann::json &j, Outer &o) {
    std::string s = j.at("inner");
    std::cout<<s<<std::endl;
    o.inner = s;
}
int main(){

    std::cout<<"here"<<std::endl;
    Outer outer = {"somya"};
    nlohmann::json j1;
    to_json(j1,outer);
    std::cout<<"here2"<<std::endl;

    Outer outer2;
    from_json(j1,outer2);
    std::cout<<"here3"<<std::endl;


    std::cout<<outer2.inner<<std::endl;
}