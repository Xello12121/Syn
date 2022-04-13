#ifndef CLIENT_SDK_MINECRAFT
#define CLIENT_SDK_MINECRAFT

#include "../Utils/Utils.h"
#include "../Mem/Mem.h"

#include "Classes/ClientInstance.h"
#include "Classes/Player.h"

class MC {
public:
    static auto getClientInstance(void) -> ClientInstance*;
    static auto getLocalPlayer(void) -> Player*;
};

#endif /* CLIENT_SDK_MINECRAFT */