#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

int main()
{
    // Create a Data object with some values
    Data data;
    data.intValue = 42;
    data.strValue = "Hello from Data!";

    std::cout << "Original Data address: " << &data << "\n";
    std::cout << "data.intValue: " << data.intValue << "\n";
    std::cout << "data.strValue: " << data.strValue << "\n\n";

    // Serialize the pointer
    uintptr_t raw = Serializer::serialize(&data);
    std::cout << "Serialized (uintptr_t): " << raw << "\n\n";

    // Deserialize back to a Data*
    Data* ptr = Serializer::deserialize(raw);
    std::cout << "Deserialized Data address: " << ptr << "\n";
    std::cout << "ptr->intValue: " << ptr->intValue << "\n";
    std::cout << "ptr->strValue: " << ptr->strValue << "\n\n";

    // Check if the pointer is the same
    if (ptr == &data)
        std::cout << "Pointer check: OK (they match!)\n";
    else
        std::cout << "Pointer check: KO (they do not match!)\n";

    return 0;
}
