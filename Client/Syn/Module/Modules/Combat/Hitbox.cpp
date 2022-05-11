#include "Hitbox.h"
#include "../../../Category/Category.h"
#include "../../../Manager/Manager.h"

auto Hitbox::onRenderOptions(void) -> void {
    
    ImGui::SliderFloat(std::string("Width").c_str(), &size.x, 0.f, 10.f);
    ImGui::SliderFloat(std::string("Height").c_str(), &size.y, 0.f, 10.f);

};

auto Hitbox::onGameMode(GameMode* GM) -> void {
    auto player = GM->player;
    
    for(auto [runtimeId, entity] : this->category->manager->entityMap) {
        if(player->runtimeId == runtimeId || !entity->isAlive())
            continue;
        
        if(types.find(entity->getEntityTypeId()) == types.end())
            types[entity->getEntityTypeId()] = Vec2<float>(entity->collision.x, entity->collision.y);
        
        entity->setSize(size.x, size.y);
    };
};

auto Hitbox::onDisable(void) -> void {
    auto manager = this->category->manager;
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