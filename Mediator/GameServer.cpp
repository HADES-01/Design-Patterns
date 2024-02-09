#include "GameServer.h"
#include <iostream>

void GameServer::join(Player *player)
{
    std::cout <<"[Server] : " << player->name << " joined the game.\n";
    player->game = this;
    players[player->name] = player;
}

void GameServer::leave(Player *player)
{
    std::cout <<"[Server] : "  << player->name << " left the game.\n";
    players.erase(player->name);
}

void GameServer::transfer(std::string name, int damage_or_health)
{
    Player *reciever = players[name];
    if(reciever == nullptr) {
        std::cout <<"[Server] : "  << name << " is not present in the game.\n";
        return;
    }
    reciever->recieve(damage_or_health);
}