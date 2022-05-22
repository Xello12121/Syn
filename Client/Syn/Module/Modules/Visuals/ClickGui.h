#ifndef CLIENT_SYN_MODULE_MODULES_VISUALS_CLICKGUI
#define CLIENT_SYN_MODULE_MODULES_VISUALS_CLICKGUI

#include "../../Module.h"

class ClickGui : public Module {
public:
    ClickGui(Category* c) : Module(c, "Click Gui") {
        this->setKey(VK_INSERT);
        this->setState(true);
    };
public:
    virtual auto onRender(void) -> void override;
    virtual auto onEnable(void) -> void override;
private:
    bool updatedWindowSize = false;
};

#endif /* CLIENT_SYN_MODULE_MODULES_VISUALS_CLICKGUI */