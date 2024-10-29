#include <map>
#include <string>
#include <iostream>
#include "include/external/nlohmann.hpp"

int main() {
    std::map<std::string, std::string> method_kind_mapping;

    method_kind_mapping["new"] = "mutate";
    method_kind_mapping["name"] = "query";
    method_kind_mapping["symbol"] = "query";
    method_kind_mapping["decimals"] = "query";
    method_kind_mapping["details"] = "query";
    method_kind_mapping["total_supply"] = "query";
    method_kind_mapping["balance_for"] = "query";
    method_kind_mapping["transfer"] = "mutate";
    method_kind_mapping["approve"] = "mutate";
    method_kind_mapping["transfer_from"] = "mutate";
    method_kind_mapping["allowance"] = "query";

    // Convert the map to JSON
    nlohmann::json json_object = method_kind_mapping;

    // Serialize the JSON object to a string
    std::string serialized_string = json_object.dump();

    // For demonstration: print the serialized JSON string
    std::cout << "Serialized JSON: " << serialized_string << std::endl;
}
