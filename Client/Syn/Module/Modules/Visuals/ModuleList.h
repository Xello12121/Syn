#ifndef CLIENT_SYN_MODULE_MODULES_VISUALS_MODULELIST
#define CLIENT_SYN_MODULE_MODULES_VISUALS_MODULELIST

#include "../../Module.h"

class ModuleList : public Module {
public:
    ModuleList(Category* c) : Module(c, "Module List") {
        this->isEnabled = true;
    };
public:
    auto onRender(Renderer*) -> void override;
public:
    float alpha = 0.f;
    auto updateAlpha(void) -> void;
};

#endif /* CLIENT_SYN_MODULE_MODULES_VISUALS_MODULELIST */