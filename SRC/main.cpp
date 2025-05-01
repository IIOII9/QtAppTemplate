#include <memory>
#include <iostream>
int main() {
    std::unique_ptr<int> ptr = std::make_unique<int>(42);
    std::cout << "Value: " << *ptr << std::endl;
    std::shared_ptr<int> shared = std::make_shared<int>(100);
    std::cout << "Shared value: " << *shared << std::endl;
    std::shared_ptr<int> shared2 = shared;
    std::cout << "Shared value: " << *shared2 << std::endl;
    return 0;
}