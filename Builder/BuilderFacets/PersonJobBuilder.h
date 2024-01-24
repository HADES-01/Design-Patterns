#include "PersonBuilder.h"

/**
 * @brief Builder for the complex Job attribute. Provides API to set company name, salary and position.
 * 
 */
class PersonJobBuilder : public PersonBuilderBase
{
public:
    PersonJobBuilder(Person &p) : PersonBuilderBase{p} {};

    // Updates company name of the person
    PersonJobBuilder &at(std::string company)
    {
        p.company = company;
        return *this;
    }
    // Updates position of the person
    PersonJobBuilder &as(std::string post)
    {
        p.position = post;
        return *this;
    }
    // Updates salary of the person
    PersonJobBuilder &earning(int salary)
    {
        p.salary = salary;
        return *this;
    }
};
