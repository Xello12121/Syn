#include "DirectionalPhase.h"
#include "../../../Category/Category.h"
#include "../../../Manager/Manager.h"

auto DirectionalPhase::onTick(void) -> void {
    auto instance = MC::getClientInstance();
    auto mcGame = (instance != nullptr ? instance->getMinecraftGame() : nullptr);

    if(mcGame == nullptr || !mcGame->canUseKeys)
        return this->setState(false);
    
    auto mgr = this->category->manager;
    
    if(!mgr->isUsingKey(this->key))
        return this->setState(false);
};

auto DirectionalPhase::onGameMode(GameMode* GM) -> void {
    auto mgr = this->category->manager;
    auto keys = mgr->keyMap;

    if(!mgr->isUsingKey(this->key))
        return this->setState(false);
    
    auto player = GM->player;
    auto myPos = *player->getPos();

    auto yaw = (player->bodyRot.y + 90.f) * (3.14 / 180.f);
    auto oMotion = player->velocity;

    myPos.x += cos(yaw) * speed;
    myPos.z += sin(yaw) * speed;

    player->setPos(&myPos);
    player->velocity = Vec3<float>(oMotion.x, 0.f, oMotion.z);

    player->setFieldOfViewModifier(3.f);
};

auto DirectionalPhase::onDisable(void) -> void {
    auto player = MC::getLocalPlayer();

    if(player == nullptr)
        return;
    
    player->setFieldOfViewModifier(1.f);
};

auto DirectionalPhase::onRenderOptions(void) -> void {
    
    ImGui::SliderFloat(std::string("Speed").c_str(), &speed, 0.1, 2.f);

};