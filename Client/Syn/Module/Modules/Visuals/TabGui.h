#ifndef CLIENT_SYN_MODULE_MODULES_VISUALS_TABGUI
#define CLIENT_SYN_MODULE_MODULES_VISUALS_TABGUI

#include "../../Module.h"

class TabGui : public Module {
public:
    TabGui(Category* c) : Module(c, "Tab GUI") {
        this->isEnabled = true;
        this->key = VK_TAB;
    };
public:
    auto onRender(Renderer*) -> void override;
    auto onKey(uint64_t, bool, bool*) -> void override;
private:
    int selCatIndex = 0, selModIndex = 0;
    bool selectedCat = false, selectedMod = false;
private:
    float selCatAnimModifier = 0.f;
    float selModAnimModifier = 0.f;
private:
    float animSpeedModifier = 4.f;
private:
    float alpha = 0.f;
    auto updateAlpha(void) -> void;
};

#endif /* CLIENT_SYN_MODULE_MODULES_VISUALS_TABGUI */