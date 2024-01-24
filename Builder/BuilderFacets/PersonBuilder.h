#pragma once
#include "Person.h"

class PersonAddressBuilder;
class PersonJobBuilder;
class PersonBuilder;

/**
 * @brief Abstraction for all the builder classes. Provide seamless transition between different builders.
 * 
 */
class PersonBuilderBase
{
protected:
    Person &p;
    explicit PersonBuilderBase(Person &p) : p(p) {}

public:

    /**
     * @brief Switches PersonBuilder to build complex Address attribute.
     * 
     * @return PersonAddressBuilder 
     */
    PersonAddressBuilder lives();

    /**
     * @brief Switches PersonBuilder to build complex Job attribute.
     * 
     * @return PersonJobBuilder 
     */
    PersonJobBuilder works();

    /**
     * @brief Moves the actual person object out of the PersonBuilder to Person variable;
     * 
     * @return Person 
     */
    operator Person() const
    {
        return std::move(p);
    }

    friend class PersonBuilder;
    friend class PersonAddressBuilder;
    friend class PersonJobBuilder;
};


/**
 * @brief Builder for the Person class and its complex attributes. Actually holds the Person object.
 */
class PersonBuilder : public PersonBuilderBase
{
    Person person;

public:
    PersonBuilder() : PersonBuilderBase{person} {};
};
