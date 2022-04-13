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
        return *(GuiData**)((uintptr_t)(this) + 0x4E8);
    };
};

#endif /* CLIENT_SDK_CLASSES_CLIENTINSTANCE */