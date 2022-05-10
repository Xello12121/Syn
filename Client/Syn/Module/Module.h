#ifndef CLIENT_SYN_MODULE_MODULE
#define CLIENT_SYN_MODULE_MODULE

#include "../../SDK/Minecraft.h"

class Category;

class Module {
public:
    Category* category = nullptr;
public:
    std::string name;
    uint64_t key = NULL;
    bool isEnabled = false, wasEnabled = false;
public:
    Module(Category*, std::string);
public:
    auto baseTick(void) -> void;
public:
    virtual auto onTick(void) -> void {};
private:
    virtual auto onEnable(void) -> void {};
    virtual auto onDisable(void) -> void {};
public:
    virtual auto onGameMode(GameMode*) -> void {};
    virtual auto onAttack(GameMode*, Actor*) -> void {};
public:
    virtual auto onRender(void) -> void {};
    virtual auto onKey(uint64_t, bool, bool*) -> void {};
};

#endif /* CLIENT_SYN_MODULE_MODULE */