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
   
   

