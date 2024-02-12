#pragma once
#include <string>

class GameServer;

/**
 * @brief Each player can only send or recieve info from the mediator GameServer.
 */
class Player
{
    std::string name;
    int health{0};
    GameServer *game{nullptr};
    friend class GameServer;

public:
    Player(std::string);
    // Send info to the Game Server regarding another player.
    void send(std::string name, int damage_or_health);
    // Recieve info from the Game Server about itself.
    void recieve(int damage_or_health);
};