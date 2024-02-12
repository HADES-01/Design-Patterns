#pragma once
#include "Player.h"
#include <string>
#include <map>

/**
 * @brief Game Server acts as a Meadiator for all the players.
 * All Players interact with the server rather than with each other.
 */
class GameServer
{
    std::string server_name;
    std::map<std::string, Player *> players;

public:
    // Allows Players to join a server.
    void join(Player *player);
    // Allows Players to leave a server.
    void leave(Player *player);
    // Establishes connection between multiple players.
    void transfer(std::string name, int damage_or_health);
};