#include "Speed.h"
#include "../../../Category/Category.h"
#include "../../../Manager/Manager.h"

auto Speed::onGameMode(GameMode* GM) -> void {

    if(msDelay > 0 && std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - savedTime) <= std::chrono::milliseconds((int)msDelay))
        return;
    
    savedTime = std::chrono::high_resolution_clock::now();

    auto instance = MC::getClientInstance();
    auto mcGame = (instance != nullptr ? instance->getMinecraftGame() : nullptr);

    if(mcGame == nullptr || !mcGame->canUseKeys)
        return;
    
    auto player = GM->player;
    auto bodyRot = player->bodyRot;

    auto mgr = this->category->manager;

    auto wKey = mgr->keyMap[0x57];
    auto sKey = mgr->keyMap[0x53];
    auto aKey = mgr->keyMap[0x41];
    auto dKey = mgr->keyMap[0x44];

    if(!wKey && !sKey && !dKey && !aKey)
        return;
    
    auto yaw = bodyRot.y;

    if (wKey) {
        if (!aKey && !dKey) {
            yaw += 90.f;
        }
        else if (aKey) {
            yaw += 45.f;
        }
        else if (dKey) {
            yaw += 135.f;
        }
    }
    else if (sKey) {
        if (!aKey && !dKey) {
            yaw -= 90.f;
        }
        else if (aKey) {
            yaw -= 45.f;
        }
        else if (dKey) {
            yaw -= 135.f;
        }
    }
    else if (!wKey && !sKey) {
        if (dKey) yaw += 180.f;
    }
    
    player->velocity = Vec3<float>(cos((yaw) * (3.14 / 180.f)) * speed, player->velocity.y, sin((yaw) * (3.14 / 180.f)) * speed);

};

auto Speed::onRenderOptions(void) -> void {
    
    ImGui::SliderFloat(std::string("Speed").c_str(), &speed, 0.1f, 2.f);
    ImGui::SliderInt(std::string("Delay").c_str(), &msDelay, 0, 5000);

};