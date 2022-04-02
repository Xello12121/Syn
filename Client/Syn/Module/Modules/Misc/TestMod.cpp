#include "TestMod.h"

auto TestModule::onTick(void) -> void {
    auto localPlayer = MC::getLocalPlayer();

    if(localPlayer == nullptr)
        return;
    
    auto lerpTo = Vec3<float>(0, .4f, 0);
    localPlayer->lerpMotion(&lerpTo);
    
    this->isEnabled = false;
};