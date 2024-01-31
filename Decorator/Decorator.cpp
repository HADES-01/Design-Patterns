/**
 * @cite Decorator Pattern states that in order to add functionality to individual objects either at runtime or compile-time, decorator classes are created that adds the required functionality either by aggregating the object or by inheriting from the object.
 * Aims at promoting Separation of Concerns and adherence to SRP and OCP.
 *
 * @brief Decorator Pattern can be exemplified by a Filter Class that might need different features as multiple filters are selected at runtime.
 * What happens when differnt Filters are mixed and matched, Do we create sub-classes for every combination possible ?
 * What happens when more than 2 filters are applied?
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/**
 * @brief Base Filter interface.
 */
class Filter
{
public:
    virtual std::string filter() = 0;
};

/**
 * @brief Filters by age.
 */
class AgeFilter : public Filter
{
public:
    std::string filter() override
    {
        return "Filter by Age";
    }
};

/**
 * @brief Filters by name.
 */
class NameFilter : public Filter
{
public:
    std::string filter() override
    {
        return "Filter by Name";
    }
};

/**
 * @brief Filters by both name and age.
 * 
 * !@warning Tightly Coupled with NameFilter and AgeFilter.
 * 
 * !@warning Other Filters will also require similar new sub-classes, which is neither efficient nor practical.
 */
class AgeAndNameFilter : public Filter
{
public:
    std::string filter()
    {
        return "Filter by Name & Filter by Age.";
    }
};

/**
 * @brief Filter by any two Filters provided.
 * 
 * *Not tightly coupled with any of the concrete implementations and works with any filters even with itself.
 */
class AndFilter : public Filter
{
    Filter *filterA;
    Filter *filterB;

public:
    AndFilter(Filter *a, Filter *b) : filterA(a), filterB(b) {}
    std::string filter()
    {
        return filterA->filter() + " & " + filterB->filter();
    }
};

/**
 * @brief New Filter introduced that filters by location.
 * 
 * !@warning Doesn't have the concrete implememntation of _and_Filter with neither Age nor Name.
 */
class LocationFilter : public Filter
{
public:
    std::string filter() override
    {
        return "Filter by Location.";
    }
};

/**
 * @brief Filter by any number of Filters provided.
 * 
 * *Not tightly coupled with any of the concrete implementations and works with any filters even with itself.
 */
class MultiFilter : public Filter
{
    std::vector<Filter *> filters;

public:
    MultiFilter(std::initializer_list<Filter *> filters) : filters(filters) {}

    std::string filter() override
    {
        std::string ans;
        for (auto filter : filters)
        {
            ans += filter->filter();
            if(filter != filters.back()) ans += " & ";
        }
        return ans;
    }
};

int main()
{
    Filter *name = new NameFilter();
    Filter *age = new AgeFilter();
    std::cout << name->filter() << "\n"
              << age->filter() << "\n";
    
    // *Filter by name & age.
    Filter *name_age = new AgeAndNameFilter();
    std::cout << name_age->filter() << "\n";

    Filter *location = new LocationFilter();
    // ! Don't have a _AndLocationFilter to filter with new LocationFilter as well.

    // *Filter by name & location.
    Filter *and_filter = new AndFilter(name, location);
    std::cout << and_filter->filter() << std::endl;

    // *Filters by name & age & location.
    Filter *multi_Filter = new MultiFilter({name, age, location});
    std::cout << multi_Filter->filter();
    
    return 0;
}