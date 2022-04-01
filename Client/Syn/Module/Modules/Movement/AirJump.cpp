#include "AirJump.h"

class Actor {
private:
    char pad_0x0000[0x1D8]; //0x0000
public:
    bool onGround;
};

auto AirJump::onTick(void) -> void {
    auto localPlayer = (Actor*)Mem::findMultiLvlPtr((uintptr_t)(GetModuleHandleA("Minecraft.Windows.exe")) + 0x045B7DE8, { 0x8, 0x18, 0xB8, 0x0 });

    if(localPlayer == nullptr)
        return;
    
    localPlayer->onGround = true;
};