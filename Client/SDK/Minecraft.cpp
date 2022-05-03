#include "Minecraft.h"

auto MC::getClientInstance(void) -> ClientInstance* {
    return (ClientInstance*)Mem::findMultiLvlPtr((uintptr_t)(GetModuleHandleA("Minecraft.Windows.exe")) + 0x045CA888, { 0xA0, 0x48, 0x8, 0x0, 0x58, 0x0 });
}

auto MC::getLocalPlayer(void) -> Player* {
    return (Player*)Mem::findMultiLvlPtr((uintptr_t)(GetModuleHandleA("Minecraft.Windows.exe")) + 0x0549E7A8, { 0x10, 0x18, 0xB8, 0x0 });
};