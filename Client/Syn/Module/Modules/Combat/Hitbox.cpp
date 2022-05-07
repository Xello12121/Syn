#include "Hitbox.h"
#include "../../../Category/Category.h"
#include "../../../Manager/Manager.h"

auto Hitbox::onGameMode(GameMode* GM) -> void {
    auto player = GM->player;
    
    for(auto [runtimeId, entity] : this->category->manager->entityMap) {
        if(player->runtimeId == runtimeId || !entity->isAlive())
            continue;
        
        if(types.find(entity->getEntityTypeId()) == types.end())
            types[entity->getEntityTypeId()] = Vec2<float>(entity->collision.x, entity->collision.y);
        
        entity->setSize(2.f, 6.f);
    };
};

auto Hitbox::onDisable(void) -> void {
    auto player = MC::getLocalPlayer();

    if(player == nullptr)
        return;
    
    for(auto [runtimeId, entity] : this->category->manager->entityMap) {
        if(player->runtimeId == runtimeId || !entity->isAlive())
            continue;
        
        if(types.find(entity->getEntityTypeId()) == types.end())
            continue;
        
        auto collision = types[entity->getEntityTypeId()];
        entity->setSize(collision.x, collision.y);
    };
};