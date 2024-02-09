#include <iostream>
#include <vector>

struct ParticipantBase
{
    int value{0};
    virtual void recieve(int a) = 0;
};

struct Mediator
{
    std::vector<ParticipantBase *> parts;
    void broadcast(int a, ParticipantBase* sender)
    {
        for (auto b : parts)
        {
            if(b == sender) continue;
            b->recieve(a);
        }
    }
};

struct Participant : ParticipantBase
{
    Mediator &med;

    Participant(Mediator &m) : med(m)
    {
        med.parts.emplace_back(this);
    }

    void say(int a)
    {
        med.broadcast(a, this);
    }

    void recieve(int a) override
    {
        value += a;
    }
};