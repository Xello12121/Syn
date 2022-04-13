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
    auto player = GM->player;
    auto myPos = *player->getPos();

    auto distances = std::vector<float>();

    for(auto [runtimeId, entity] : this->category->manager->entityMap) {
        if(player->runtimeId == runtimeId || !entity->isAlive())
            continue;
        
        if(entity->getEntityTypeId() == 64 || entity->getEntityTypeId() == 69)
            continue;
        
        auto dist = getDistBetween(myPos, *entity->getPos());
        
        if(dist <= 12.f)
            distances.push_back(dist);
    };

    std::sort(distances.begin(), distances.end());

    if(distances.empty())
        return;
    
    for(auto [runtimeId, entity] : this->category->manager->entityMap) {
        if(player->runtimeId == runtimeId || !entity->isAlive())
            continue;
        
        auto dist = getDistBetween(myPos, *entity->getPos());
        
        if(dist == distances[0] || (distances.size() >= 2 ? dist == distances[1] : distances.back()) || (distances.size() >= 3 ? dist == distances[2] : distances.back())) {
            GM->attack(entity);
            player->swing();
        };
    };
};