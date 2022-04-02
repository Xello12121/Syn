#include "TestMod.h"

auto TestModule::onTick(void) -> void {
    auto localPlayer = MC::getLocalPlayer();

    if(localPlayer == nullptr)
        return;

    this->isEnabled = false;
};