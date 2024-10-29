#include <variant>
#include <string>
#include <iostream>

std::variant<int, std::string> f(const std::string& tokenId) {
    return "ir4";
}
int main(){
      std::variant<int, std::string> result = f("1");

        std::string error = std::get<std::string>(result);

        std::cout<<error<<std::endl;

}