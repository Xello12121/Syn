#ifndef CLIENT_SYN_MODULE_MODULES_MISC_NUKER
#define CLIENT_SYN_MODULE_MODULES_MISC_NUKER

#include "../../Module.h"

class Nuker : public Module {
public:
    Nuker(Category* c) : Module(c, "Nuker") {
        //
    };
public:
    auto onStartDestroyBlock(GameMode*, Vec3<int>*, uint8_t, bool*) -> void override;
    auto onContinueDestroyBlock(GameMode*, Vec3<int>*, uint8_t blockFace, Vec3<float>*, bool*) -> void override;
public:
    auto onRenderOptions(void) -> void override;
private:
    int range = 4;
};

#endif /* CLIENT_SYN_MODULE_MODULES_MISC_NUKER */