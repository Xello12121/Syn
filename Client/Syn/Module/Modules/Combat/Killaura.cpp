#include "Killaura.h"
#include "../../../Category/Category.h"
#include "../../../Manager/Manager.h"

auto getDistBetween(Vec3<float> posA, Vec3<float> posB) -> float {
    auto dX = posA.x - posB.x;
    auto dY = posA.y - posB.y;
    auto dZ = posA.z - posB.z;

    return sqrt(dX * dX + dY * dY + dZ * dZ);
};

auto Killaura::onGameMode(GameMode* GM) -> void {
    if(msDelay > 0 && std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - savedTime) <= std::chrono::milliseconds((int)msDelay))
        return;
    
    savedTime = std::chrono::high_resolution_clock::now();

    auto player = GM->player;
    auto myPos = *player->getPos();

    auto distances = std::vector<float>();

    for(auto [runtimeId, entity] : this->category->manager->entityMap) {
        if(player->runtimeId == runtimeId || !entity->isAlive() || entity->isNotMob())
            continue;
        
        auto add = false;
        
        if(entity->getEntityTypeId() == EntityType::Client_Player && attackPlayers)
            add = true;
        
        if(entity->isHostileType()) {
            if(attackHostiles)
                add = true;
        } else {
            if(attackPassives)
                add = true;
        };
        
        if(!add)
            continue;
        
        auto dist = getDistBetween(myPos, *entity->getPos());
        
        if(dist <= 12.f)
            distances.push_back(dist);
    };

    std::sort(distances.begin(), distances.end());

    if(distances.empty())
        return;
    
    for(auto [runtimeId, entity] : this->category->manager->entityMap) {
        if(player->runtimeId == runtimeId || !entity->isAlive() || entity->isNotMob())
            continue;
        
        auto add = false;
        
        if(entity->getEntityTypeId() == EntityType::Client_Player && attackPlayers)
            add = true;
        
        if(entity->isHostileType()) {
            if(attackHostiles)
                add = true;
        } else {
            if(attackPassives)
                add = true;
        };
        
        if(!add)
            continue;
        
        auto dist = getDistBetween(myPos, *entity->getPos());
        
        if(dist == distances[0] || (distances.size() > 1 ? dist == distances[0] : dist == distances[1]) || (distances.size() > 2 ? dist == distances[1] : dist == distances[2])) {
            GM->attack(entity);
            player->swing();
        };
    };
};

auto Killaura::onRenderOptions(void) -> void {
    
    ImGui::SliderInt(std::string("Delay").c_str(), &msDelay, 0, 5000);

    ImGui::Spacing();
    
    ImGui::Checkbox(std::string("Players").c_str(), &attackPlayers);

    ImGui::Spacing();
    
    ImGui::Checkbox(std::string("Hostiles").c_str(), &attackHostiles);
    ImGui::Checkbox(std::string("Passives").c_str(), &attackPassives);

};