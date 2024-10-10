#include <iostream>
#include <memory>
#include <vector>

// MemorySegment class as defined
class MemorySegment {
public:
    MemorySegment(size_t len) 
        : data_(std::make_unique<std::vector<uint8_t>>(len)) {}

    uint8_t* get() const {
        return data_->data();
    }

    size_t size() const {
        return data_->size();
    }

private:
    std::unique_ptr<std::vector<uint8_t>> data_;
};

// Runtime class with allocate method
class Runtime {
public:
    uint8_t* allocate(size_t len) {
        auto segment = new MemorySegment(len);
        return segment->get();
    }
};

// Test function for MemorySegment and Runtime::allocate
void test_memory_allocation() {
    Runtime runtime;
    size_t allocation_size = 16;  // Allocate 16 bytes of memory

    // Allocate memory using Runtime::allocate
    uint8_t* allocated_memory = runtime.allocate(allocation_size);

    // Ensure that the memory is allocated and accessible
    if (allocated_memory != nullptr) {
        std::cout << "Memory allocated successfully!" << std::endl;
    } else {
        std::cerr << "Memory allocation failed!" << std::endl;
    }

    // Set the allocated memory to specific values for testing
    for (size_t i = 0; i < allocation_size; ++i) {
        allocated_memory[i] = static_cast<uint8_t>(i);  // Assign values 0, 1, 2, ...
    }

    // Output the memory contents to verify
    std::cout << "Allocated memory contents: ";
    for (size_t i = 0; i < allocation_size; ++i) {
        std::cout << static_cast<int>(allocated_memory[i]) << " ";  // Print each byte value
    }
    std::cout << std::endl;
}

int main() {
    test_memory_allocation();
    return 0;
}
