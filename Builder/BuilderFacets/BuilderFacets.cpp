/**
 * @cite Builder Facets is a combination of Builder and Facade Pattern and is used when the object being built is highly complex and requires the use of multiple builders.
 * Aims at making the API more verbose and readable.
 *
 * @brief Builder Facets can be exemplified by a Person class that has multiple complex attributes (like address, job, family etc.).
 * Building the Person using a single builder will violate the Single Responsibilty principle as the builder will have to build all the complex attributes itself.
 * We can divide the build process into multiple steps and multiple builders.
 */

#include <string>
#include <iostream>
#include "Person.h"
#include "PersonBuilder.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"

// g++ *.cpp -o BuilderFacets && .\BuilderFacets.exe

int main()
{
    // Initialization is highly verbose and easy to understand
    Person p = Person::create()
                   .lives()
                   .at("1/2-A, London Street")
                   .in("London")
                   .at_code("110033")
                   .works()
                   .at("Google Inc.")
                   .as("Software Developer")
                   .earning(1e6);

    std::cout << p;
    return 0;
}