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
};

#endif /* CLIENT_SYN_MODULE_MODULES_VISUALS_TABGUI */