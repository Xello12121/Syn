#ifndef CLIENT_SDK_CLASSES_CLIENTINSTANCE
#define CLIENT_SDK_CLASSES_CLIENTINSTANCE

#include "GuiData.h"
#include "MinecraftGame.h"

class ClientInstance {
public:
    auto getMinecraftGame(void) -> MinecraftGame* {
        return *(MinecraftGame**)((uintptr_t)(this) + 0xA8);
    };
public:
    auto getGuiData(void) -> GuiData* {
        return (GuiData*)Mem::findMultiLvlPtr(0x05470AA0, { 0x110, 0x20, 0xBC, 0x0 });
    };
};

#endif /* CLIENT_SDK_CLASSES_CLIENTINSTANCE */