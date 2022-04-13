#include "AirJump.h"

auto AirJump::onGameMode(GameMode* GM) -> void {
    auto player = GM->player;
    
    if(player != nullptr)
        player->onGround = true;
};