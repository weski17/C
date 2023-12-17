#include "example.h"
#include <iostream>

// Default constructor definition
Example::Example() = default;

// Constructor definition
Example::Example(int data) : privateData(data) {
    std::cout << "Constructor called." << std::endl;
}

// Member function to display privateData
void Example::displayPrivateData() {
    std::cout << "Private Data: " << privateData << std::endl;
}

// Friend function definition
void funktion(Example& obj) {
    int s = obj.privateData + 2;
    std::cout << "Friend Function accessing privateData: " << s << std::endl;
}
