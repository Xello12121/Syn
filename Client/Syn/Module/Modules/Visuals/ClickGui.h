#ifndef CLIENT_SYN_MODULE_MODULES_VISUALS_CLICKGUI
#define CLIENT_SYN_MODULE_MODULES_VISUALS_CLICKGUI

#include "../../Module.h"

class ClickGui : public Module {
public:
    ClickGui(Category* c) : Module(c, "Click Gui") {
        this->key = VK_INSERT;
        this->isEnabled = true;
    };
public:
    virtual auto onRender(void) -> void override;
private:
    bool setSize = true;
};

#endif /* CLIENT_SYN_MODULE_MODULES_VISUALS_CLICKGUI */