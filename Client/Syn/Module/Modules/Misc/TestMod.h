#ifndef CLIENT_SYN_MODULE_MODULES_MISC_TESTMOD
#define CLIENT_SYN_MODULE_MODULES_MISC_TESTMOD

#include "../../Module.h"

class TestModule : public Module {
public:
    TestModule(Category* c) : Module(c, "TestModule") {
        this->isEnabled = true;
    };
public:
    auto onRender(void) -> void override;
    auto onEnable(void) -> void override;
private:
    bool updatedWindowSize = false;
};

#endif /* CLIENT_SYN_MODULE_MODULES_MISC_TESTMOD */