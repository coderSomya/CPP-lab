#include <iostream>
#include "include/external/nlohmann.hpp"
#include <string>
#include <cassert>

struct WeilValue {
    std::string state; // Use string directly; "null" as a placeholder
    std::string ok_val;
};

inline void to_json(nlohmann::json &j, const WeilValue &wv) {
    j["ok_val"] = wv.ok_val;
    if (wv.state == "null") {
        j["state"] = nullptr; // Represent "null" string as JSON null
    } else {
        j["state"] = wv.state; // Serialize state normally
    }
}

inline void from_json(const nlohmann::json &j, WeilValue &wv) {
    wv.ok_val = j["ok_val"];
    if (j.contains("state") && !j["state"].is_null()) {
        wv.state = j["state"].get<std::string>(); // Deserialize state normally
    } else {
        wv.state = "null"; // Represent missing/null state as the "null" string
    }
}

void test_serialization() {
    // Case 1: Normal state
    WeilValue wv1{"active", "ok_value"};
    nlohmann::json j1 = wv1;
    assert(j1["state"] == "active");
    assert(j1["ok_val"] == "ok_value");

    // Deserialize back
    WeilValue wv1_deserialized = j1.get<WeilValue>();
    assert(wv1_deserialized.state == "active");
    assert(wv1_deserialized.ok_val == "ok_value");

    // Case 2: Null state (represented as "null" string)
    WeilValue wv2{"null", "ok_value"};
    nlohmann::json j2 = wv2;
    assert(j2["state"].is_null());
    assert(j2["ok_val"] == "ok_value");

    // Deserialize back
    WeilValue wv2_deserialized = j2.get<WeilValue>();
    assert(wv2_deserialized.state == "null");
    assert(wv2_deserialized.ok_val == "ok_value");

    // Case 3: Missing state
    nlohmann::json j3 = R"({"ok_val": "ok_value"})"_json;
    WeilValue wv3 = j3.get<WeilValue>();
    assert(wv3.state == "null"); // Default to "null" if state is missing
    assert(wv3.ok_val == "ok_value");

    // Serialize back
    nlohmann::json j3_serialized = wv3;
    assert(j3_serialized["state"].is_null());
    assert(j3_serialized["ok_val"] == "ok_value");

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    test_serialization();
    return 0;
}
