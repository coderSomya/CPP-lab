#include <iostream>
#include <string>
#include <charconv>

bool isConvertibleToInt(const std::string& str) {
    if (str.empty()) return false;

    int value;
    auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), value);

    return ec == std::errc() && ptr == str.data() + str.size();
}

int main() {
    std::string test1 = "123";
    std::string test2 = "12abc";
    std::string test3 = "-456";
    std::string test4 = "+789";
    std::string test5 = "-";
    std::string test6 = "+";
    std::string test7 = "2147483648";

    std::cout << isConvertibleToInt(test1) << '\n';
    std::cout << isConvertibleToInt(test2) << '\n'; 
    std::cout << isConvertibleToInt(test3) << '\n'; 
    std::cout << isConvertibleToInt(test4) << '\n'; 
    std::cout << isConvertibleToInt(test5) << '\n'; 
    std::cout << isConvertibleToInt(test6) << '\n'; 
    std::cout << isConvertibleToInt(test7) << '\n'; 

    return 0;
}
