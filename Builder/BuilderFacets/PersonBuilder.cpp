#include "PersonBuilder.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"

PersonAddressBuilder PersonBuilderBase::lives()
{
    return PersonAddressBuilder{p};
}

PersonJobBuilder PersonBuilderBase::works()
{
    return PersonJobBuilder{p};
}
