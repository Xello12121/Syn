#ifndef CLIENT_SYN_MODULE_MODULES_MOVEMENT_AIRJUMP
#define CLIENT_SYN_MODULE_MODULES_MOVEMENT_AIRJUMP

#include "../../Module.h"

class AirJump : public Module {
public:
    AirJump(Category* c) : Module(c, "AirJump") {
        //
    };
public:
    auto onKey(uint64_t, bool, bool*) -> void override;
};

#endif /* CLIENT_SYN_MODULE_MODULES_MOVEMENT_AIRJUMP */