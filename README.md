# Design Patterns
Design patterns are recurring solutions to common design problems in software development. They provide a template for solving specific issues in a flexible and reusable way. By encapsulating best practices, design patterns promote maintainability, scalability, and clarity in software design.

1. **[SOLID](SOLID/)**
    - [Single Responsibility](SOLID/SingleResponsibility/SingleResponsibility.cpp)
    - [Open-Closed](SOLID/OpenClosed/OpenClosed.cpp)
    - [Liskov's Substitution](SOLID/LiskovsSubstitution/LiskovsSubstitution.cpp)
    - [Interface Segregation](SOLID/InterfaceSegregation/InterfaceSegregation.cpp)
    - [Dependency Inversion](SOLID/DependencyInversion/DependencyInversion.cpp)
2. **Gamma Categorization (Erich Gamma)**
    - Categorizes design patterns based on their real-world applications i.e which part of the code they usually appear in.
    - Divides design patterns into following three categories
      - **Creational Patterns**
        1. Used when the object is being created or constructed.
        2. *Implicit Creational Patterns* - where the contructor call is not needed to create the object.
        3. *Explicit Creational Patterns* - where constructor is explicitly called to create the object.
        4. *Wholesale Object Createion* - where object is created with a single statement
        5. *Piecewise Object Creation* - where multiple steps have to followed for object creation.
        6. Singleton, Factory, Abstract, Builder and Prototype are examples of *Creational Patterns*.
      - **Structural Patterns**
        1. Used to define the structure of class e.g. how an interface is implemented or how the class member are defined.
        2. Focuses on good API design and relationship between objects.
        3. Adapter, Bridge, Composite, Decorator, Facade, Flyweight and Proxy are examples of *Structural Patterns*.
      - **Behavioral Patterns**
        1. Have on general theme to them.
        2. Ususally focuses on creating algorithms and establishing communication mechanism between different objects. 
        3. Command, Iterator, Mediator, Observer, Visitor, etc are examples of *Behavioral Patterns*.
3. **[Builder Pattern](Builder/Builder.cpp)**
   - Builder Pattern is a type of Piecewise Creational Patterns.
   - Fluent Builders allow users to chain the build commands together like `builder.do_this().do_that()`.
   - [Groovy-Style Builders](Builder/Groovy/GroovyBuilder.cpp) allow users to create *Domain-Specific Languages* that makes use of *uniform initialization* e.g. The nested groovy-style initialization looks `A{ B{ }, C{ D{ } } }`.
   - [Builder-Facets](Builder/BuilderFacets/BuilderFacets.cpp) is a combination of Builder and Facade Pattern and is used when the object being built is highly complex and requires the use of multiple builders.
4. **[Factory Pattern](Factory/Factory.cpp)**
   - Factory Pattern is a type of Wholesale Creational Pattern where the entire building process is handed over to a factory method or a factory class to avoid any convoluted API for object creation.
   - *Factory Method*, *Factory Class* and *Abstract Factory Class* are all type of Factory Pattern.
   - *[Abstract Factory Classes](Factory/AbstractFactory/AbstractFactory.cpp)* are used to create heirarchy of factories that create different object in the heirarchy.
5. **[Prototype Pattern](Prototype/Prototype.cpp)**
   - Prototype Pattern is a type of Creational Pattern where the new object is built by making modifications on an already existing complex object, or a prototype, by creating its **deep copy**, or **cloning** it. 
   - Prototyping can also be done via serialization as serialization traverses the entire object graph and needs serlialization implementation for each of the object present in it and the object that was serialized when deserialized creates a deep copy of the same.
6. **[Singleton Pattern](Singleton/Singleton.cpp)**
   - Singleton Pattern is a form of Creational Pattern where an object is or should be instatntiated only once.
   - Singleton pattern e.g. is used when the constructor call is expensive and we need to provide the same instance to everyone. 
   - It also allows lazy instantiation and thread safety.
   - *Monostate Pattern* is a variation of Singleton Pattern where all the data members of the class are static and getters and setter are called for them. This pattern is highly prone to bugs and not very inheritance-friendly due to the static members.
   - *[Multiton Pattern](Singleton/Multiton/Multiton.cpp)* is also a variation of Singleton Pattern where multiple singleton objects are created based on a given range or keys.
7. **[Adapter Pattern](Adapter/Adapter.cpp)**
   - Adapter Pattern is a form of Structural Pattern where a given interface is '*adapted*' or transformed to conform to the required interface.
   - Used when the given interface doesn't have the required functionality out of the box or if it doesn't conform to the required structural specs e.g. exposes some internal data that should be private in your program's context or if the given interface might change in the future.
8. **[Bridge Pattern](Bridge/Bridge.cpp)**
   - Bridge Pattern is a type of Structural Pattern where an interface(heirarchy) is decoupled from its implementation(heirarchy) so that the two can vay independently.
   - It is useful when there are two orthogonal dependencies that need to evolve independently, allowing changes in one heirarchy to not affect the other and to also avoid '[Cartesian Entity Explosion](EXTRAS.md#cartesian-entity-explosion)'.
   - *[Pimpl Idiom Pattern](EXTRAS.md#pimpl-idiom-pattern)* is also a variation of Bridge Pattern.
9. **[Composite Pattern*](Composite/Composite.cpp)**
   - Composite Pattern is a variation of Structural Pattern that allows user to interact with both scalar or composite objects uniformly i.e. through the same API.
10. **[Decorator Pattern*](Decorator/Decorator.cpp)**
    - Decorator Pattern is another variation of Structural Pattern which facilitates the addition of behaviours to individual objects.
    - Decorator Pattern can be implemented in C++ by Aggregating the existing object or by inherting from the decorated object.
11. **[Facade Pattern](Facade/Facade.cpp)**
    - Facade Pattern is a type of Strucutural Pattern where an easy-to-use or a simpler API is build on top of a rather complex collection of sub-sytems, trying to provide a unified interface over the interfaces of the multiple sub-sytems.
    - Facade Pattern can be seen in the [*BuilderFacets*](Builder/BuilderFacets/BuilderFacets.cpp) example where the a simpler API of `PersonBuilder` is provide to initialize the collection of multiple complex attributes.
12. **[Flyweight Pattern](Flyweight/Flyweight.cpp)**
    - Flyweight Pattern is a form of Structural Pattern which helps in reducing memory usage by sharing the objects with similar states across multiple contexts. 
    - It is useful when a large number of objects with same states have to be created and each object is either very large or creating the object adds significant overhead.
13. **[Proxy Pattern](Proxy/Proxy.cpp)**
    - Proxy Pattern is another type of Structural Pattern which is used to create an interface for a resource in order to control access to it as the resource might be expensive, difiicult to construct or requires added functionality.
    - Key difference between Proxy and Decorator Pattern is that a Proxy provides an identical interface by replicating the members, adds the required functionalities to the redefined members, whereas a Decorator provides an enhanced interface to the underlying resource by aggregating the resource.
    - Simplest Examples of Proxy Pattern are the *[smart_pointers](EXTRAS.md#smart-pointers-unique-shared-and-weak)* of STL library.
14. **[Chain Of Responsibility](CoR/CoR.cpp)**
    - Chain of Responsibility is a Behavioral Pattern which allows a object to pass the request along a chain of potential handlers until one of them handles the request.
    - It decouples the sender of an object fromm its reciever by giving more than one object the chance to handle the request.
15. **[Command Pattern](Command/Command.cpp])**
    - Command Pattern is a Behavioral Pattern in which each operation/command performed is stored as an object that contains all the information required to perform the operation/command.
    - It provides useful functionality like undoable commands, command queues, macro commands etc.
    - *[Commad Query Separation](EXTRAS.md#command-query-separation)* is variation of Command Pattern.
16. **[Interpreter Pattern](Interpreter/Interpreter.cpp)**
    - Interpreter Pattern is a type of Behavioral Pattern that is used to process structured textual data by the process of lexing and and parsing.
    - *Lexing* is the process of separating the text into lexical tokens (tokens that have some meaning like 'class' keyword in C++).
    - *Parsing* is the process of turning the tokens into machine understandable statements.
    - Modern Language compiler use the interpreter to parse the code.
17. **[Interator Pattern](Iterator/Iterator.cpp)**
    - Iterator Pattern is a variation of Behavioral Pattern that provides an API to traverse a data structure.
    - An iterator object keeps a reference to the current element and knows how to move to the next element.
    - All the data structures in C++ STL have iterators that allows their traversal.