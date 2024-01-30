#include <iostream>

/**
 * @brief Base class that delegates the method calls to the required type T at runtime.
 * 
 * @tparam T type of the Derived classes.
 */
template <typename T>
class Base
{
public:
    // Casts the 'this' to the typename and calls the overrided function.
    void a()
    {
        static_cast<T *>(this) -> a();
    }
};

/**
 * @brief Derives from the Base class with a type of itself.
 */
class Derived1 : public Base<Derived1>
{
public:
    void a()
    {
        std::cout << "Derived1::a() callled. \n";
    }
};


/**
 * @brief Derives from the Base class with a type of itself.
 */
class Derived2 : public Base<Derived2>
{
public:
    void a()
    {
        std::cout << "Derived2::a() called. \n";
    }
};

int main()
{
    // Creating a Base pointer of type 'Derived1'
    Base<Derived1> *b = new Derived1();

    // a() of Derived1 will be called when the base ptr is casted to Derived1 type.
    b->a();
    
    // Creating a Base pointer of type 'Derived2'
    Base<Derived2> *c = new Derived2();

    // a() of Derived2 will be called when the base ptr is casted to Derived2 type.
    c->a();
    return 0;
}