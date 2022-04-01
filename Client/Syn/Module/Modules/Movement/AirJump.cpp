#include "AirJump.h"

auto AirJump::onTick(void) -> void {
    auto localPlayer = (uintptr_t*)Mem::findMultiLvlPtr((uintptr_t)(GetModuleHandleA("Minecraft.Windows.exe")) + 0x045B7DE8, { 0x8, 0x18, 0xB8, 0x0 });

    if(localPlayer == nullptr)
        return;
    
    *(bool*)((uintptr_t)(localPlayer) + 0x1D8) = true;
};