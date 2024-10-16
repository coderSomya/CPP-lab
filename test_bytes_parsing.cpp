#include <iostream>
#include "include/external/nlohmann.hpp"
#include <vector>
#include <string>
#include <cstring>
#include <stdexcept>

// Function to convert serialized bytes (buffer) to the desired type V
template<typename V>
V deserializeFromBuffer(const std::string& buffer) {
    // Step 1: Parse the buffer using nlohmann::json
    // If buffer is already in JSON format, this will work fine for basic types.
    nlohmann::json j = nlohmann::json::parse(buffer);

    // Step 2: Convert JSON object to the type V
    V v = j.get<V>();

    return v;
}

// Specialization for non-JSON compatible types if needed (for advanced scenarios)
template <>
std::vector<uint8_t> deserializeFromBuffer<std::vector<uint8_t>>(const std::string& buffer) {
    std::vector<uint8_t> byteVector(buffer.begin(), buffer.end());
    return byteVector;
}

// General wrapper function to convert bytes from memory to a custom type V
template <typename V>
V getFromMemory(uintptr_t mem_ptr, size_t len) {
    // Step 1: Extract the serialized string from the memory pointer (starting after the length prefix)
    std::string buffer(reinterpret_cast<char*>(mem_ptr + 1 + 4), len);

    // Step 2: Deserialize the buffer into the desired type V
    return deserializeFromBuffer<V>(buffer);
}

int main() {
    try {
        // Example usage:
        // Simulating the pointer to a memory location (for demo purposes)
        std::vector<uint8_t> memory = {0, 0, 0, 0, 5, 'H', 'e', 'l', 'l', 'o'};
        uintptr_t mem_ptr = reinterpret_cast<uintptr_t>(memory.data());
        size_t len = 5;  // Length of the data to be read from memory

        // Retrieve data as a string
        std::string result = getFromMemory<std::string>(mem_ptr, len);
        std::cout << "Deserialized string: " << result << std::endl;

        // Retrieve data as a vector of bytes
        std::vector<uint8_t> byteResult = getFromMemory<std::vector<uint8_t>>(mem_ptr, len);
        std::cout << "Deserialized byte vector: ";
        for (auto byte : byteResult) {
            std::cout << static_cast<int>(byte) << " ";
        }
        std::cout << std::endl;

        // Add more types like int32_t, float, or custom types based on user specialization needs
        // int32_t resultInt = getFromMemory<int32_t>(mem_ptr, len);
        // std::cout << "Deserialized int: " << resultInt << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
