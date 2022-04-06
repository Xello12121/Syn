#include "TestMod.h"
#include "../../../Category/Category.h"
#include "../../../Manager/Manager.h"

auto TestModule::onTick(void) -> void {
    auto localPlayer = MC::getLocalPlayer();

    if(localPlayer == nullptr)
        return;
    
    for(auto [runtimeId, entity] : this->category->manager->entityMap) {
        if(runtimeId == localPlayer->runtimeId)
            continue;
        
        entity->setTarget(localPlayer);
    };
};