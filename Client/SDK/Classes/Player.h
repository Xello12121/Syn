#ifndef CLIENT_SDK_CLASSES_PLAYER
#define CLIENT_SDK_CLASSES_PLAYER

#include "Actor.h"
#include "GameMode.h"

class Player : public Actor {
public:
    auto setFlightSpeed(float f) -> void {
        *(float*)((uintptr_t)(this) + 0x7C0) = f;
    };
};

#endif /* CLIENT_SDK_CLASSES_PLAYER */