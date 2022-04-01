#include "AirJump.h"
bool once = false;

auto AirJump::onTick(void) -> void {
    auto localPlayer = MC::getLocalPlayer();
    
    if(localPlayer == nullptr)
        return;
    
    localPlayer->onGround = true;
};