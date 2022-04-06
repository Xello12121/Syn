#include "Manager.h"

#include "../Category/Category.h"
#include "../Module/Module.h"

Manager::Manager(Client* client) {
    this->client = client;
    this->initHooks();
    this->init();
};

typedef void (__thiscall* Actor_BlockSource)(Actor*, void*, void*);
Actor_BlockSource _Actor_BlockSource;

Manager* actorBlkMgr = nullptr;

auto Actor_BlockSource_Callback(Actor* e, void* a2, void* a3) -> void {
    
    if(actorBlkMgr != nullptr)
        actorBlkMgr->entityMap[e->runtimeId] = e;

    _Actor_BlockSource(e, a2, a3);
};

auto Manager::initHooks(void) -> void {
    actorBlkMgr = this;
    
    if(MH_Initialize() != MH_OK)
        return Utils::debugLog("Failed to initialize MinHook!");
    
    auto sig = Mem::findSig("48 89 5C 24 08 4C 89 44 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 83 EC 60");

    if(!sig)
        return Utils::debugLog("Failed to find Sig for Actor_BlockSource");
    
    if(MH_CreateHook((void*)sig, &Actor_BlockSource_Callback, reinterpret_cast<LPVOID*>(&_Actor_BlockSource)) != MH_OK)
        return Utils::debugLog("Failed to create hook for Actor_BlockSource");
    
    MH_EnableHook((void*)sig);
};

#include "../Module/Modules/Movement/AirJump.h"
#include "../Module/Modules/Misc/TestMod.h"

auto Manager::init(void) -> void {
    if(this->categories.empty()) {
        auto names = { "Combat", "Movement", "Player", "Visuals", "World", "Misc" };

        for(auto name : names)
            new Category(this, name);
    };

    if(this->categories.empty())
        return;
    
    /* Combat */
    
    auto combat = this->getCategory("Combat");

    if(combat != nullptr) {
        /* Add Modules */
    };

    /* Movement */
    
    auto movement = this->getCategory("Movement");

    if(movement != nullptr) {
        new AirJump(movement);
    };

    /* Player */

    auto player = this->getCategory("Player");

    if(player != nullptr) {
        /* Add Modules */
    };

    /* Visuals */

    auto visuals = this->getCategory("Visuals");

    if(visuals != nullptr) {
        /* Add Modules */
    };

    /* World */

    auto world = this->getCategory("World");

    if(world != nullptr) {
        /* Add Modules */
    };

    /* Misc */

    auto misc = this->getCategory("Misc");

    if(misc != nullptr) {
        new TestModule(misc);
    };

    for(;;) {
        for(auto c : this->categories)
            c->baseTick();
    };
};

auto Manager::getCategory(std::string name) -> Category* {
    for(auto c : this->categories)
        if(c->name.rfind(name) != std::string::npos)
            return c;
    return nullptr;
};

auto Manager::getCategory(size_t i) -> Category* {
    if(this->categories.empty() || (this->categories.size() - 1) < i)
        return nullptr;
    
    return this->categories.at(i);
};