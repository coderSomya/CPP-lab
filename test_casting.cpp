#include <iostream>
#include <string>
#include <optional>
#include <vector>
#include "include/external/nlohmann.hpp"

// Mock the external functions for demonstration purposes
uintptr_t read_collection(uintptr_t ptr) {
    // Mocked behavior - return a valid pointer (for testing)
    return static_cast<uintptr_t>(ptr);
}

intptr_t read_bulk_collection(uintptr_t ptr) {
    // Mocked behavior - return a valid pointer (for testing)
    return static_cast<intptr_t>(ptr);
}

std::string read_bytes_from_memory(intptr_t ptr) {
    // Mocked behavior - pretend that memory holds this string for testing
    return "{\"example_key\": \"example_value\"}";
}

std::vector<uint8_t> get_length_prefixed_bytes_from_string(const std::string& str, int prefix) {
    // Mock behavior of prefixing with length and converting string to bytes
    std::vector<uint8_t> bytes(str.begin(), str.end());
    return bytes;
}

// Memory class
class Memory {
public:
    template <typename V>
    std::optional<V> read_collection(const std::string& key) {
        auto raw_key = get_length_prefixed_bytes_from_string(key, 0);
        std::cout << "Raw Key (as bytes): ";
        for (auto b : raw_key) {
            std::cout << std::hex << static_cast<int>(b) << " ";
        }
        std::cout << std::dec << std::endl;

        uintptr_t ptr1 = reinterpret_cast<uintptr_t>(raw_key.data());
        std::cout << "Ptr1: " << ptr1 << std::endl;

        intptr_t ptr = ::read_collection(ptr1);  // Changed to intptr_t
        std::cout << "Ptr (from read_collection): " << ptr << std::endl;

        try {
            auto buffer = read_bytes_from_memory(ptr);
            std::cout << "Buffer (from read_bytes_from_memory): " << buffer << std::endl;
            return nlohmann::json::parse(buffer).get<V>(); 
        } catch (const std::runtime_error& e) {
            if (std::string(e.what()).find("KeyNotFoundInCollection") != std::string::npos) {
                return std::nullopt;
            }
            throw e;
        }
    }

    // For bulk collection
    template <typename V>
    std::string read_bulk_collection(const std::string& prefix) {
        auto raw_prefix = get_length_prefixed_bytes_from_string(prefix, 0);
        std::cout << "Raw Prefix (as bytes): ";
        for (auto b : raw_prefix) {
            std::cout << std::hex << static_cast<int>(b) << " ";
        }
        std::cout << std::dec << std::endl;

        uintptr_t ptr1 = reinterpret_cast<uintptr_t>(raw_prefix.data());
        std::cout << "Ptr1: " << ptr1 << std::endl;

        intptr_t ptr = ::read_bulk_collection(ptr1);  // Changed to intptr_t
        std::cout << "Ptr (from read_bulk_collection): " << ptr << std::endl;

        std::string buffer = read_bytes_from_memory(ptr);
        std::cout << "Buffer (from read_bytes_from_memory): " << buffer << std::endl;

        return buffer;
    }
};

// Test function for both methods
void test_read_functions() {
    Memory memory;

    // Test read_collection expecting an object
    std::optional<nlohmann::json> result = memory.read_collection<nlohmann::json>("example_key");
    if (result) {
        std::cout << "Result from read_collection: " << result->dump(4) << std::endl; // Dump the JSON object nicely
    } else {
        std::cout << "Key not found in collection." << std::endl;
    }

    // Test read_bulk_collection
    std::string bulk_result = memory.read_bulk_collection<std::string>("example_prefix");
    std::cout << "Result from read_bulk_collection: " << bulk_result << std::endl;
}

int main() {
    test_read_functions();
    return 0;
}
