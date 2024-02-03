#include <string>

struct Person
{
    Person(int age) : age(age) {}
    void set_age(int age) { this->age = age; };
    std::string drive() { return "driving"; }
    std::string drink() { return "drinking"; }
    std::string drink_and_drive() { return "dead"; }
    friend struct ResponsiblePerson;

private:
    int age;
};

struct ResponsiblePerson
{
    Person &p;
    ResponsiblePerson(Person &p) : p(p) {}

    void set_age(int age) { p.age = age; }
    std::string drive()
    {
        if (p.age >= 16)
            return p.drive();
        return "too young";
    }
    std::string drink()
    {
        if (p.age >= 18)
            return p.drink();
        else
            return "too young";
    }
    std::string drink_and_drive() { return p.drink_and_drive(); }
};
