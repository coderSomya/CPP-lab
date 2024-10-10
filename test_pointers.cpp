#include <iostream>
#include <vector>
#include <cstring>

// Helper function for testing
std::vector<uint8_t> get_length_prefixed_bytes_from_string(const std::string& payload, uint8_t is_error) {
    std::vector<uint8_t> buffer;
    uint32_t len = payload.size();
    buffer.push_back(is_error);  // Add error flag (1 byte)
    buffer.insert(buffer.end(), reinterpret_cast<const uint8_t*>(&len), reinterpret_cast<const uint8_t*>(&len) + 4);  // Add length (4 bytes)
    buffer.insert(buffer.end(), payload.begin(), payload.end());  // Add payload (message)
    return buffer;
}

// Test the read_bytes_from_memory behavior
void test_read_bytes_from_memory(uint8_t* mem_ptr) {
    // Read error flag (1 byte)
    uint8_t is_error = mem_ptr[0];

    // Read length (next 4 bytes)
    uint32_t len = 0;
    std::memcpy(&len, mem_ptr + 1, 4); // Copy 4 bytes into len

    // Extract the message (starting from byte 5)
    std::string message(reinterpret_cast<char*>(mem_ptr + 5), len);

    // Output the results
    std::cout << "Error Flag: " << static_cast<int>(is_error) << std::endl; // Print as int to display as 0 or 1
    std::cout << "Length: " << len << std::endl;
    std::cout << "Message: " << message << std::endl;
}

int main() {
    // Create a test payload with error flag, length, and message
    std::string test_message = "Hello, this is a test!";
    uint8_t is_error = 1;  // Simulating an error flag (set to 1)
    std::vector<uint8_t> test_data = get_length_prefixed_bytes_from_string(test_message, is_error);

    // Pass the pointer to test function
    test_read_bytes_from_memory(test_data.data());

    return 0;
}
