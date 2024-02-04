#include <memory>
#include <iostream>

int main()
{
    std::unique_ptr<int> ptr = std::make_unique<int>(32);


    std::cout << *ptr << "\n";
    *ptr = 10;
    std::cout << *ptr << "\n";

    // std::unique_ptr<int> ptr2 = ptr;

    std::unique_ptr<int> ptr2 = std::move(ptr);
    
    std::cout << *ptr2 << " " ;

    // std::shared_ptr<int> 

    return 0;
}