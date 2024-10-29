#include "include/external/nlohmann.hpp"
#include <string>
#include <iostream>

  std::string base_state_path(){ 
    return std::to_string(4); 
  }


template <typename K>
  std::string state_tree_key(const K &key) {
    if constexpr (std::is_same<K, std::string>::value) {
        // If the key is already a string, return it without extra quotes
        return base_state_path() + "_" + key;
    } else {
        // Otherwise, convert key to JSON string and append
        return 
        base_state_path() + "_" + nlohmann::json(key).dump();
    }
    // return base_state_path() + "_" + nlohmann::json(key).dump();
  }


int main(){
std::string key = "3";
std::string res = nlohmann::json(key).dump();    
// std::cout<<res<<std::endl;
// std::cout<<key<<std::endl;
// std::string value = "3";
// int value = 4;
//     nlohmann::json jsonPayload = value;
//     std::string serializedPayload = jsonPayload.dump();
//     std::cout<<serializedPayload<<std::endl;

// std::string a = state_tree_key<std::string>("3");
// std::string b = state_tree_key<int>(4);
// std::cout<<a<<" "<<b<<std::endl;
using T  =  std::string;
T tokenId = "7";
if(tokenId == "7"){
  std::cout<<"yes1"<<std::endl;
}
if(std::string(tokenId)==std::string("7")){
  std::cout<<"yes2"<<std::endl;
}
}


