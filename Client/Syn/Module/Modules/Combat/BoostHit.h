#ifndef CLIENT_SYN_MODULE_MODULES_COMBAT_BOOSTHIT
#define CLIENT_SYN_MODULE_MODULES_COMBAT_BOOSTHIT

#include "../../Module.h"

class BoostHit : public Module {
public:
    BoostHit(Category* c) : Module(c, "Boost Hit") {
        //
    };
public:
    auto onAttack(GameMode*, Actor*) -> void override;
    auto onRenderOptions(void) -> void override;
private:
    float boost = 1.2f;
};

#endif /* CLIENT_SYN_MODULE_MODULES_COMBAT_BOOSTHIT */