#ifndef CLIENT_SYN_MODULE_MODULES_MOVEMENT_DIRECTIONALPHASE
#define CLIENT_SYN_MODULE_MODULES_MOVEMENT_DIRECTIONALPHASE

#include "../../Module.h"

class DirectionalPhase : public Module {
public:
    DirectionalPhase(Category* c) : Module(c, "Directional Phase") {
        this->key = 0x47; /* G */
    };
public:
    auto onTick(void) -> void override;
public:
    auto onGameMode(GameMode*) -> void override;
    auto onDisable(void) -> void override;
public:
    auto onRenderOptions(void) -> void override;
private:
    float speed = 0.4f;
};

#endif /* CLIENT_SYN_MODULE_MODULES_MOVEMENT_DIRECTIONALPHASE */