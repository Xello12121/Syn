#include "Minecraft.h"
#include "Classes/Player.h"

auto MC::getClientInstance(void) -> ClientInstance* {
    return (ClientInstance*)Mem::findMultiLvlPtr(0x05473C38, { 0x0, 0x48, 0x0 });
};

auto MC::getLocalPlayer(void) -> Player* {
    auto player = (Player*)Mem::findMultiLvlPtr(0x0549E798, { 0x8, 0x20, 0xC8, 0x0 });
    auto level = (player != nullptr ? player->getLevel() : nullptr);

    return level != nullptr ? (Player*)level->getPrimaryLocalPlayer() : nullptr;
};