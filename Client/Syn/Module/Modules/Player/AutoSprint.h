#ifndef CLIENT_SYN_MODULE_MODULES_PLAYER_AUTOSPRINT
#define CLIENT_SYN_MODULE_MODULES_PLAYER_AUTOSPRINT

#include "../../Module.h"

class AutoSprint : public Module {
public:
    AutoSprint(Category* c) : Module(c, "AutoSprint") {
        //
    };
public:
    virtual auto onGameMode(GameMode*) -> void override;
};

#endif /* CLIENT_SYN_MODULE_MODULES_PLAYER_AUTOSPRINT */