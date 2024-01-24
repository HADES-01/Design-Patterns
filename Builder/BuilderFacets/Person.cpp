#include "Person.h"
#include "PersonBuilder.h"

PersonBuilder Person::create()
{
    return PersonBuilder{};
}

std::ostream &operator<<(std::ostream &os, const Person &p)
{
    return os << "Person lives at " << p.address << ", " << p.city << "-" << p.post_code
              << " and works at " << p.company << " as a " << p.position << " earning $" << p.salary << ".\n";
}