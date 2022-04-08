#include "TestMod.h"
#include "../../../Category/Category.h"
#include "../../../Manager/Manager.h"

auto TestModule::onGameMode(GameMode* GM) -> void {
    auto player = GM->player;
    auto myPos = *player->getPos();

    for(auto [runtimeId, entity] : this->category->manager->entityMap) {
        if(player->runtimeId == runtimeId)
            continue;
        
        auto entPos = *entity->getPos();

        auto dX = myPos.x - entPos.x;
        auto dY = myPos.y - entPos.y;
        auto dZ = myPos.z - entPos.z;

        auto dist = sqrt(dX * dX + dY * dY + dZ * dZ);

        if(dist <= 12.f) {
            GM->attack(entity);
            player->swing();
        };

        entity->setSize(2.f, 6.f);
    };
};