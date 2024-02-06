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

### Curiously Recurring Template Pattern (CRTP)
- It is a method of performing runtime polymorphism without the use of virtual functions. It is done by using Template classes and figuring out at runtime the type of the class that has called the method.
- In this method the V_TABLE and V_PTR are not created thus not inflating the class size and the type of the object is determined by casting the base class pointer to the typename and then calling the required method. This makes sure that the method called actually belongs to the typename.
- CRTP is also faster then the virtual approach as it circumvents the need of creating V_TABLE and V_PTR altogether.
- [Example](C++Concepts/CRTP/CRTP.cpp) represents the above usecase.

### Smart Pointers (unique, shared and weak)
- Smart Pointers are a proxy created over the raw pointers present in the C++ that allows for automatic Garbage Collection, Resource Ownership and prevention of Memory Leaks.
- Smart Pointers are stack allocated objects that act as pointers to heap-allocated objects, and as the Smart Pointer goes out of scope it also releases the heap-memory allowing Automatic Garbage Collection and prevention of Memory Leaks.
- `std::unique_ptr`
  1. It implements Singular Resource Ownership semantics in C++.
  2. It makes sure that only one instance of `std::unique_ptr` owns the resource object at a given moment i.e Exclusive Ownership.
- `std::shared_ptr`
  1. It implements Shared Resource Ownership semantics in C++.
  2. Allows multiple `std::shared_ptr` to be the owners of the same object(done by reference counting) and releases the object when the last owner goes out of scope or is reset.
- `std::weak_ptr`
  1. It implements Non-Owning References in C++.
  2. A `std::weak_ptr` allows access to the object managed by shared_ptr that doesn't participate in the refrence counting nor does it extends the lifetime of the object.
- [Example](C++Concepts/SmartPointers/SmartPointers.cpp) illustrates all 3 variations.

### Command Query Separation
- Variation of Command Pattern where the Command/Operation object is divided into 2 different entites namely, Command and Queries.
- **Command** - refers to the commands/operations that requests changes in the system.
- **Query** - refers to the commands/operations that requests information about the state of the system.
- Adds another layer of abstraction over the Command Pattern API in order differntiate between Commands & Queries and possibly handle them diffrerently as well.
- Used in databases in order to separately handle the read/Query operations and write/Command operations to improve latency and throughput.