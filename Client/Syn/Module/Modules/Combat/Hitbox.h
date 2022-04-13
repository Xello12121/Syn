#ifndef CLIENT_SYN_MODULE_MODULES_COMBAT_HITBOX
#define CLIENT_SYN_MODULE_MODULES_COMBAT_HITBOX

#include "../../Module.h"

class Hitbox : public Module {
public:
    Hitbox(Category* c) : Module(c, "Hitbox") {
        //
    };
public:
    virtual auto onGameMode(GameMode*) -> void override;
    virtual auto onDisable(void) -> void override;
private:
    std::map<uint8_t, Vec2<float>> types;
};

#endif /* CLIENT_SYN_MODULE_MODULES_COMBAT_HITBOX */