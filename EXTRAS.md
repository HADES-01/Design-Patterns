### Cartesian Entity Explosion
- Refers to a situtation, where as the number of options and features in a system increases then the number of combinations (cartesian-product) that needs to be supported also increases exponentially leading to complex and unmanageable codebase.
- For example, If there is Application that needs support for Windows and Mac operating systems and both 64-bit and 32-bit architectures, it will need 4 entities just to support these 2 features with just 2-2 variations respectively. 
- Lets say in the near future, we need to extend support to linux and one other OS, then the number of entites will become 8. The no of entities doubled by introducing just 2 more options. This is know as Cartesian Entity Exlposion.

### Pimpl Idiom Pattern
- Pointer-to-implementation Pattern also known as Compiler Firewall Idiom or Cheshire Cat Technique is a method of hiding implemetation details of a class from its public interface.
- It uses a pointer to a inner implemetation class that usually lies in the `.cpp` files and gets complied into binaries, thus not be visible to the user.
- It achieves better encapsulation by hiding away implemetation details into binaries and also reduces the user compile time as they don't have to recompile the library headers due to some update that doesn't concern the API rather they just have to get the updated pre-compiled binaries with required changes.
```cpp
// Person.h
// Will be used by the user.
class Person {
    class PersonImpl; // Inner implementation class forward declared.
    PersonImpl *impl; // Pointer-to-Implemetation
public:
    void a();
};
```
```cpp
// Person.cpp
// Will be compiled to binary.
class Person::PersonImpl {
public:
    void a(Person *p) {
        // Actual Implementation of a().
    }
};

void Person::a() {
    impl->a(this); // delegating functionality to Implemetation class.
}

```