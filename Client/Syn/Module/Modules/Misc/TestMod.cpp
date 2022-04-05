#include "TestMod.h"

auto TestModule::onTick(void) -> void {
    auto localPlayer = MC::getLocalPlayer();

    if(localPlayer == nullptr)
        return;
    
    localPlayer->setScoreTag("Test");
    Utils::debugLog(localPlayer->getScoreTag());

    this->isEnabled = false;
};