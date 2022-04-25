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
    auto onRender(void) -> void override;
    auto onKey(uint64_t, bool, bool*) -> void override;
private:
    float alpha = 0.f;
private:
    auto updateAlpha(void) -> void;
    auto getScale(void) -> float;
private:
    bool selectedCat = true, selectedMod = false;
    int selCatIndex = 0, selModIndex = 0;
private:
    float animModifier = 0.05f;
    float selCatAnimOff = 0.f;
    float selModAnimOff = 0.f;
};

#endif /* CLIENT_SYN_MODULE_MODULES_VISUALS_TABGUI */