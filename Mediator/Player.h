#pragma once
#include <string>

class GameServer;

class Player
{
    std::string name;
    int health{0};
    GameServer *game{nullptr};
    friend class GameServer;

public:
    Player(std::string);
    void send(std::string name, int damage_or_health);
    void recieve(int damage_or_health);
};