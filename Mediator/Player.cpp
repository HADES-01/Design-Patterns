#include "Player.h"
#include "GameServer.h"
#include <algorithm>
#include <iostream>

Player::Player(std::string name) : game{game}, health{100}, name{name} {}

void Player::send(std::string name, int damage_or_health)
{
    std::cout << "[" << this->name << "] : " << (damage_or_health < 0 ? " attacked " : " healed ") << name << "\n";
    if (health > 0)
        game->transfer(name, damage_or_health);
}

void Player::recieve(int damage_or_health)
{
    health = std::clamp(health + damage_or_health, 0, 100);
    std::cout << "[" << this->name << "] : " << " now at " << health << "\n";
}