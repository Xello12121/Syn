#include "AirJump.h"

auto AirJump::onKey(uint64_t key, bool isDown, bool* cancel) -> void {
    auto instance = MC::getClientInstance();
    auto mcGame = (instance != nullptr ? instance->getMinecraftGame() : nullptr);
    
    if(!isDown || key != VK_SPACE || mcGame == nullptr)
        return;
    
    if(!mcGame->canUseKeys)
        return;
    
    auto player = MC::getLocalPlayer();
    
    if(player == nullptr)
        return;
    
    auto lerpTo = Vec3<float>(0.f, 0.45f, 0.f);
    player->lerpMotion(&lerpTo);
};