#include "AirJump.h"

auto AirJump::onTick(void) -> void {
    auto localPlayer = MC::getLocalPlayer();
    
    if(localPlayer == nullptr)
        return;
    
    *(bool*)((uintptr_t)(localPlayer) + 0x1D8) = true;
};