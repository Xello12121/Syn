#include "Minecraft.h"

auto MC::getClientInstance(void) -> ClientInstance* {
    return (ClientInstance*)Mem::findMultiLvlPtr(0x05473C38, { 0x0, 0x48, 0x0 });
};

auto MC::getLocalPlayer(void) -> Player* {
    return (Player*)Mem::findMultiLvlPtr(0x0549E7A8, { 0x18, 0x18, 0xB8, 0x0 }); /* WIP */
};