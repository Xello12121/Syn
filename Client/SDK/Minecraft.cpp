#include "Minecraft.h"

auto MC::getLocalPlayer(void) -> Player* {
    return (Player*)Mem::findMultiLvlPtr((uintptr_t)(GetModuleHandleA("Minecraft.Windows.exe")) + 0x045B7DE8, { 0x8, 0x18, 0xB8, 0x0 });
};