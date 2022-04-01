#include "AirJump.h"
bool once = false;

auto AirJump::onTick(void) -> void {
    auto localPlayer = MC::getLocalPlayer();
    
    if(localPlayer == nullptr)
        return;
    
    localPlayer->onGround = true;

    if(!once) {
        once = true;

        auto myPos = *localPlayer->getPos();
        auto msg = std::string("X: " + std::to_string(myPos.x) + ", Y: " + std::to_string(myPos.y) + ", Z: " + std::to_string(myPos.z));

        Utils::debugLog(msg);
    };
};