#include <iostream>
#include <optional>
#include <variant>
#include <string>

std::variant<int, double, std::string> processValue(const std::optional<int>& opt) {
    if (opt.has_value()) {
        if (opt.value() % 2 == 0) {
            return opt.value();
        } else {
            return 3.14;
        }
    }
    return "No value";
}

struct node{
    int n;
    std::string s;
};

void check(std::optional<int> n){
    int val = n.value_or(2);
    node n1{
        val,
        "somya"
    };

    std::cout<<n1.n<<std::endl;
}

std::optional<uint32_t> f(int x){
    if(x%2) return x;
}

int main() {
    // std::optional<int> opt1 = 42;
    // std::optional<int> opt2 = 15;
    // std::optional<int> opt3;

    // auto result1 = processValue(opt1);
    // auto result2 = processValue(opt2);
    // auto result3 = processValue(opt3);

    // std::visit([](auto&& arg) {
    //     std::cout << "Result1 holds: " << arg << '\n';
    // }, result1);

    // std::visit([](auto&& arg) {
    //     std::cout << "Result2 holds: " << arg << '\n';
    // }, result2);

    // std::visit([](auto&& arg) {
    //     std::cout << "Result3 holds: " << arg << '\n';
    // }, result3);

    int a;
    int b = 7;

    check(a);
    check(b);

    return 0;

    int c;
    // c = f(12);
}
