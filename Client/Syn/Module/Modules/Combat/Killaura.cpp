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
        
        auto add = true;
        
        if(entity->getEntityTypeId() == EntityType::Client_Player && !attackPlayers)
            add = false;
        
        if(entity->isHostileType() && !attackHostiles)
            add = false;
        else if(!entity->isHostileType() && !attackPassives)
            add = false;
        
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
        
        auto add = true;
        
        if(entity->getEntityTypeId() == EntityType::Client_Player && !attackPlayers)
            add = false;
        
        if(entity->isHostileType() && !attackHostiles)
            add = false;
        else if(!entity->isHostileType() && !attackPassives)
            add = false;
        
        if(!add)
            continue;
        
        auto dist = getDistBetween(myPos, *entity->getPos());
        
        if(dist == distances[0] || (distances.size() >= 2 ? dist == distances[1] : distances.back()) || (distances.size() >= 3 ? dist == distances[2] : distances.back())) {
            GM->attack(entity);
            player->swing();
        };
    };
};

auto Killaura::onRenderOptions(void) -> void {
    
    ImGui::SliderInt(std::string("Delay (MS)").c_str(), &msDelay, 0, 5000);

    ImGui::Spacing();
    
    ImGui::Checkbox(std::string("Players").c_str(), &attackPlayers);

    ImGui::Spacing();
    
    ImGui::Checkbox(std::string("Hostiles").c_str(), &attackHostiles);
    ImGui::Checkbox(std::string("Passives").c_str(), &attackPassives);

};