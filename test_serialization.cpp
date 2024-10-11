#include <iostream>
#include "include/external/nlohmann.hpp"

struct Person {
    std::string name;
    int age;
    std::string city;
};

// Implement to_json and from_json
void to_json(nlohmann::json& j, const Person& p) {
    j = nlohmann::json{{"name", p.name}, {"age", p.age}, {"city", p.city}};
}

void from_json(const nlohmann::json& j, Person& p) {
    j.at("name").get_to(p.name);
    j.at("age").get_to(p.age);
    j.at("city").get_to(p.city);
}

int main() {

    Person person{"Alice", 25, "Paris"};

    // Serialize 
    nlohmann::json json_data = person;
    std::string json_str = json_data.dump(); // Serialize to string
    
    std::cout << "Serialized JSON string: " << json_str << std::endl;

    // Deserialize JSON string back to Person object using nlohmann::json::parse
    nlohmann::json parsed_json = nlohmann::json::parse(json_str);
    Person deserialized_person = parsed_json.get<Person>();

    // Output deserialized data
    std::cout << "Deserialized Person: " << deserialized_person.name << ", " 
              << deserialized_person.age << ", " << deserialized_person.city << std::endl;

    return 0;
}
