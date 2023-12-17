#include "GenericClass.h"
#include <iostream>
#include <string>

int main() {
    
    GenericClass<int> intObj(42);
    std::cout << "Integer Data: " << intObj.getData() << std::endl;

 
    GenericClass<std::string> stringObj("Hello, C++");
    std::cout << "String Data: " << stringObj.getData() << std::endl;

    return EXIT_SUCCESS;
}
