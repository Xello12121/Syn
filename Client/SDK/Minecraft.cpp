#include "Minecraft.h"

auto MC::getLocalPlayer(void) -> Player* {
    return (Player*)Mem::findMultiLvlPtr((uintptr_t)(GetModuleHandleA("Minecraft.Windows.exe")) + 0x04596CF8, { 0x0, 0x58, 0xD0, 0x278, 0x0 });
};