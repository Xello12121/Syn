#ifndef CLIENT_SYN_MODULE_MODULES_MOVEMENT_SPEED
#define CLIENT_SYN_MODULE_MODULES_MOVEMENT_SPEED

#include "../../Module.h"

class Speed : public Module {
public:
    Speed(Category* c) : Module(c, "Speed") {
        //
    };
public:
    auto onGameMode(GameMode*) -> void override;
    auto onRenderOptions(void) -> void override;
private:
    float speed = 0.6f;
    int msDelay = 0;
private:
    std::chrono::time_point<std::chrono::steady_clock> savedTime = std::chrono::high_resolution_clock::now();
};

#endif /* CLIENT_SYN_MODULE_MODULES_MOVEMENT_SPEED */