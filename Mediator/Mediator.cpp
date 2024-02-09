/**
 * @cite Mediator Pattern states that in order to establish communication between multiple components, a central component(mediator) should be set up so that the components don't have to directly interact with each other.
 * Aims at promoting modularization by decoupling all the components from each other.
 *
 * @brief Mediator Pattern can be exemplified by an Online Game that needs multiple players to interact with each other.
 * It can be done using a Server as a mediator that keeps references to all the players. 
 */

#include "GameServer.h"
#include "Player.h"
#include <iostream>

int main()
{
    Player john{"John"};
    Player jane{"Jane"};
    Player jacob{"Jacob"};

    GameServer game;
    game.join(&john);
    game.join(&jane);
    game.join(&jacob);

    jane.send("John", -20);

    jacob.send("John", 10);

    game.leave(&jacob);
    jane.send("Jacob", -20);

    return 0;
}