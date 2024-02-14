/**
 * @cite Observer Pattern states that in order to notify components about some event that occurs in the system, then the components should observe the event and be able to handle them as well.
 * Aims at promoting flexibility and maintainablity by decoupling the observer and observable.
 *
 * @brief Observer Pattern can be exemplified by NewsLetter class that sends out newsletters to its subscribers.
 * How to only notify the people that are subscribed about the new newsletter?
 * How to provide people with the unsubscribe functionality ?
 */

#include <iostream>
#include <set>
#include <string>

// Forward Declaration of Observer
template <typename>
class Observer;

/**
 * @brief Template Abstraction for Observable 
 */
template <typename T>
class Observable
{
protected:
    // Keeps track of all the subscribers
    std::set<Observer<T> *> observers;

public:
    // Notifes all the subscribers
    void notify(T &source, std::string news)
    {
        for (auto observer : observers)
            observer->news(source, news);
    }

    // Allows Person to subscribe
    void subscribe(Observer<T> &sub)
    {
        observers.insert(&sub);
    }

    // Allows Person to unsubscribe
    void unsubscribe(Observer<T> &unsub)
    {
        observers.erase(&unsub);
    }
};

/**
 * @brief NewsLetter that Person can subscribe to and recieve news.
 */
class NewsLetter : public Observable<NewsLetter>
{
public:
    // Publish new news to subscribers
    void new_news(std::string news)
    {
        notify(*this, news);
    }
};

/**
 * @brief Template Abstractions for Observers
 */
template <typename T>
class Observer
{
public:
    // Observes the new news that is published.
    virtual void news(T &source, std::string new_news) = 0;
};

/**
 * @brief Person that can subsrcibe to the NewsLetter.
 */
class Person : public Observer<NewsLetter>
{
    std::string name;

public:
    Person(std::string name) : name(name) {}

    // Receive new news from the subscribed NewsLetter.
    void news(NewsLetter &source, std::string new_news) override
    {
        std::cout << "News Recieved by " << name << " :: " << new_news << std::endl;
    }
};

int main()
{
    Person jon{"Jon"};
    Person jane{"Jane"};
    NewsLetter nl;

    nl.subscribe(jane);
    
    nl.new_news("Lost Dog !!!");
    std::cout << std::endl;

    nl.subscribe(jon);
    nl.new_news("Found Dog !!!");
    std::cout << std::endl;

    nl.unsubscribe(jane);
    nl.new_news("Lost Dog Again !!!");
    return 0;
}