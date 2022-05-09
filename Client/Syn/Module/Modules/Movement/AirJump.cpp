#include "AirJump.h"
#include "../../../Category/Category.h"
#include "../../../Manager/Manager.h"

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
    
    auto vel = player->velocity;
    vel.y = 0.4f;

    player->ascendBlockByJumping();
    player->lerpMotion(&vel);
};