#include "AirJump.h"

auto AirJump::onKey(uint64_t key, bool isDown, bool* cancel) -> void {
    auto player = MC::getLocalPlayer();
    
    if(!isDown || key != VK_SPACE || player == nullptr)
        return;
    
    //
};