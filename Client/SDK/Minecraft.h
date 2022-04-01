#ifndef CLIENT_SDK_MINECRAFT
#define CLIENT_SDK_MINECRAFT

#include "../Utils/Utils.h"
#include "../Mem/Mem.h"

#include "Classes/Actor.h"

class MC {
public:
    static auto getLocalPlayer(void) -> Actor*;
};

#endif /* CLIENT_SDK_MINECRAFT */