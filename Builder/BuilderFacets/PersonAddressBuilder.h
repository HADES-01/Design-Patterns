#pragma once
#include "Person.h"

/**
 * @brief Builder for complex Address attribute. Provide API to set city, stree address and post code.
 */
class PersonAddressBuilder: public PersonBuilderBase
{
public:
    PersonAddressBuilder(Person &p): PersonBuilderBase{p} {}

    // Updates street address of the person.
    PersonAddressBuilder& at(std::string add) {
        p.address = add;
        return *this;
    }
    // Updates city of the person.
    PersonAddressBuilder& in(std::string city) {
        p.city = city;
        return *this;
    }
    // Updates postal code of the person.
    PersonAddressBuilder& at_code(std::string code) {
        p.post_code = code;
        return *this;
    }

};
