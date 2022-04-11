#include "Minecraft.h"

auto MC::getLocalPlayer(void) -> Player* {
    return (Player*)Mem::findMultiLvlPtr((uintptr_t)(GetModuleHandleA("Minecraft.Windows.exe")) + 0x04501D50, { 0x458, 0x38, 0x8, 0x240, 0x0 });
};