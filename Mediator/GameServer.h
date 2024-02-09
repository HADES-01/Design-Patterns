#pragma once
#include "Player.h"
#include <string>
#include <map>

class GameServer
{
    std::string server_name;
    std::map<std::string, Player *> players;

public:
    void join(Player *player);
    void leave(Player *player);
    void transfer(std::string name, int damage_or_health);
};