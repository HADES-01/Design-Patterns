/**
 * @cite Chain of Responsibility states that a request should be handled by a series of handlers, each of which can either process the request or pass it along the chain of handlers.
 * Aims at increasing modularity as the request handling is decoupled or separated from the reciever and the sender.    
 *
 * @brief Chain Of Responsibility can be exemplified by a Linked List of PurchaseHandlers that handles the purchase requests based on their level of authority to approve a purchase request.
 */

#include <iostream>
#include <string>

/**
 * @brief Level of Clearance that a request requires.
 */
enum ClearanceLevel
{
    LOW,
    MEDIUM,
    HIGH,
    HIGHEST
};

/**
 * @brief Abstraction for all personnel in a firm.
 */
class RequestHandler
{
protected:
    // Points to the next person in the chain of command.
    RequestHandler *next;
    // Denotes the level of clearance of the current person.
    ClearanceLevel clearance_level;
    // Denotes the name of the employee.
    std::string name;
    // Denotes the employee's post in the firm.
    std::string post;

public:
    RequestHandler(
        std::string name,
        std::string post,
        ClearanceLevel level,
        RequestHandler *next = NULL) : name(name), post(post), clearance_level(level), next(next) {}

    /**
     * @brief Adds the person that next up in the Chain of Command.
     */
    void answerable_to(RequestHandler *boss)
    {
        next = boss;
    }

    /**
     * @brief Process the request based on the clearnace level of the request and the clearance level of the employee.
     */
    void process_request(ClearanceLevel level)
    {
        if (level <= clearance_level)
        {
            std::cout << name << "(" << post << ")"
                      << " approved the request\n";
            return;
        }
        if (next)
        {
            std::cout << "Request passed on from " << name << "(" << post << ")\n";
            next->process_request(level);
        }
        else
            std::cout << "Request can't be processed.\nNo one with required clearnace is present at the moment.\n";
    };
};

/**
 * @brief Concrete Implementation for an Employee with the lowest Clearance Level.
 */
class Employee : public RequestHandler
{
public:
    Employee(const std::string &name) : RequestHandler(name, "Employee", ClearanceLevel::LOW) {}
};

/**
 * @brief Concrete Implementation for the Manager that is just above the Employee in the chain of command.
 */
class Manager : public RequestHandler
{
public:
    Manager(const std::string &name) : RequestHandler(name, "Manager", ClearanceLevel::MEDIUM) {}
};

/**
 * @brief Concrete Implementation for the Director that is just above the Manager in the chain of command.
 */
class Director : public RequestHandler
{
public:
    Director(const std::string &name) : RequestHandler(name, "Director", ClearanceLevel::HIGH) {}
};

/**
 * @brief Concrete Implementation for the CEO that is highest up in the chain of Ccommand.
 */
class CEO : public RequestHandler
{
public:
    CEO(const std::string &name) : RequestHandler(name, "CEO", ClearanceLevel::HIGHEST) {}
};

int main()
{
    // Creating the Personnel of the firm.
    CEO Justin("Justin");
    Director Jacob("Jacob");
    Manager John("John");
    Employee Jason("Jason");

    // Setting up the heirarchy of the firm.
    Jason.answerable_to(&John);
    John.answerable_to(&Jacob);
    Jacob.answerable_to(&Justin);

    // Processing Request of HIGH Level.
    Jacob.process_request(ClearanceLevel::HIGH);

    std::cout << "\n";
    // Processing Request of HIGHEST Level.
    Jason.process_request(ClearanceLevel::HIGHEST);

    // If CEO was not in office....
    Jacob.answerable_to(nullptr);
    // And HIGHEST clearance level request came in ...
    std::cout << "\n";
    Jacob.process_request(ClearanceLevel::HIGHEST);
    return 0;
}