#pragma once
#include <string>
#include <iostream>

class PersonBuilder;
class PersonAddressBuilder;
class PersonJobBuilder;

/**
 * @brief Holds Details of a Person. Has 2 complex attributes Address and Job.
 */
class Person
{
    // complex attribute address' details.
    std::string address, post_code, city;

    // complex attribute job's details.
    std::string company, position;
    int salary;

    // Constructor is private so that object can't be created directly.
    Person() {}

public:
    /**
     * @brief API to create the Person using PersonBuilder class.
     *
     * @return PersonBuilder
     */
    static PersonBuilder create();
    friend std::ostream &operator<<(std::ostream &os, const Person &p);

    friend class PersonAddressBuilder;
    friend class PersonBuilder;
    friend class PersonJobBuilder;
};