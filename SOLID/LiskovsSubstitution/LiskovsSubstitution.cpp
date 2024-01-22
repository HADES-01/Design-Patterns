/**
 * @cite Liskov's Substitution Principle states that the object of a superclass should be replacable with the object of a derived class without breaking any functionality
 * Aims at promoting extensibility and flexibility as the APIs written for the superclass are reusable for all of the derived classes as well
 *
 * @brief Liskov's Substitution Principle can be exemplified by a Bird class that was created with the thought that all birds can fly.
 * What happens when we extend bird to create an object of a fligtless bird?
 *
 */

#include <iostream>
#include <vector>
/**
 * @brief Generic Bird class assuming all birds can fly.
 *
 */
class Bird
{
public:
    virtual void fly() {};
};

/**
 * @brief Piegon class doesn't break Liskov's Substitution as it can fly.
 *
 */
class Piegon : public Bird
{
public:
    void fly() override
    {
        std::cout << "Piegon Flying ...\n";
    }
};

/**
 * @brief Ostrich class breaks Liskov's Substitution as Ostriches are flighless birds and can't fly.
 * ! @warning Making an Ostrich fly will result in an error
 */
class Ostrich : public Bird
{
public:
    void fly() override
    {
        throw std::runtime_error("Ostriches can not fly ...");
    }
};

/**
 * @brief API that consumes the bird object and tries to make them fly.
 * Also assumes that all birds can fly.
 * 
 * ! @warning Will result in an error if the object of any flightless bird is given.
 * 
 * @param birds Birds to fly
 */
void make_birds_fly(std::vector<Bird *> birds)
{
    for (auto bird : birds)
        bird->fly();
}

int main()
{
    Bird *p = new Piegon; 
    Bird *o = new Ostrich;
    std::vector<Bird*> birds = {p, o};
    try{
        // ! Will result in an error as ostriches are flightless birds.
        make_birds_fly(birds);
    } catch (std::exception &e) {
        std::cout << "ERROR :: " << e.what()  << std::endl;
    }
    return 0;
}