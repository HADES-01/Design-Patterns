/**
 * @cite Dependency Inversion Principle states that high-level modules shouldn't depend on low-level modules rather both should depend on abstractions or interfaces also abstractions shouldn't depend on details rather details should depend on abstractions.
 * Aims at Extensibility and Modularity as the codebase becomes less coupled.
 *
 * @brief Dependency Inversion Principle can be exemplified by a Animal interface and a AnimalSpeaker class that closely depends on an extension of Animal.
 * What happens when an extension of Animal that has a different implementation is passed to AnimalSpeaker?
 */

#include <string>
#include <vector>
#include <iostream>

/**
 * @brief Generic Animal Class or an Animal interface
 * 
 */
class Animal
{
public:
    virtual void make_noise() = 0;
};

/**
 * @brief Extension of Animal that stores noise as a `std::string`.
 * Low-level Module that depends on abstractions
 */
class Dog : public Animal
{
public:
    std::string noise = "Woof!!";
    void make_noise() override
    {
        std::cout << noise << std::endl;
    }
};

/**
 * @brief Extension of Animal that stores noise as a `char[]`.
 * Low-level Module that depends on abstractions
 */
class Cat : public Animal
{
public:
    char noise[10] = "Meow!!";
    void make_noise() override
    {
        std::cout << noise << std::endl;
    }
};

/**
 * @brief High-level Module that depends on low-level module.
 * !@warning Closely coupled with Dog extension of Animal class
 */
class AnimalSpeaker
{
public:
    AnimalSpeaker(Animal *animal)
    {
        // ! Imitates tight-coupling by only working if the object is of dog type
        Dog *dog = dynamic_cast<Dog*>(animal);
        if(!dog) throw std::runtime_error("Not a dog object !!!");
        dog->make_noise();
    }
};

/**
 * @brief High-level module that depends on abstraction.
 */
class BetterAnimalSpeaker
{
public:
    BetterAnimalSpeaker(Animal *animal)
    {
        animal->make_noise();
    }
};

int main()
{
    Dog dog;
    Cat cat;
    std::vector<Animal *> animals = {&dog, &cat};

    for(auto animal: animals){
        try
        {
            // ! @warning This results in an error as AniamlSpeaker is tightly coupled with Dog sub-class of Animal
            AnimalSpeaker _(animal);
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error :: " << e.what() << '\n';
        }
        BetterAnimalSpeaker __(animal);
    } 

    return 0;
}