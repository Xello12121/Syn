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

Manager* hookMgr = nullptr;

auto Actor_BlockSource_Callback(Actor* e, void* a2, void* a3) -> void {
    
    if(hookMgr != nullptr)
        hookMgr->entityMap[e->runtimeId] = e;

    _Actor_BlockSource(e, a2, a3);
};

typedef void (__thiscall* GameMode_Tick)(GameMode*);
GameMode_Tick _GameMode_Tick;

auto GameMode_Tick_Callback(GameMode* GM) -> void {
    auto player = GM->player;
    auto level = (player != nullptr ? player->getLevel() : nullptr);

    if(level != nullptr) {
        for(auto [runtimeId, entity] : hookMgr->entityMap) {
            if(level->fetchEntity(runtimeId, false) == nullptr)
                hookMgr->entityMap.erase(runtimeId);
        };

        for(auto category : hookMgr->categories) {
            for(auto mod : category->modules) {
                if(mod->isEnabled)
                    mod->onGameMode(GM);
            };
        };
    };

    _GameMode_Tick(GM);
};

typedef long(__fastcall* PresentD3D12)(IDXGISwapChain*, UINT, UINT);
PresentD3D12 oPresentD3D12;

IDXGISwapChain* pSwapChain = nullptr;
ID3D12Device* pDevice = nullptr;

Renderer* renderer = nullptr;

auto hookPresentD3D12(IDXGISwapChain3* pChain, UINT syncInterval, UINT flags) -> HRESULT {
    
    if(renderer == nullptr) {
        renderer = new Renderer();

        pSwapChain = pChain;

        if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(pDevice), reinterpret_cast<void**>(&pDevice))))
            pSwapChain->GetDevice(__uuidof(pDevice), reinterpret_cast<void**>(&pDevice));
    };

    renderer->init(pChain, pDevice);
    renderer->beginFrame();

    for(auto category : hookMgr->categories) {
        for(auto mod : category->modules) {
            if(mod->isEnabled)
                mod->onRender(renderer);
        };
    };

    renderer->endFrame();
    renderer->releaseTextures();

    return oPresentD3D12(pSwapChain, syncInterval, flags);
};

typedef void(__thiscall* KeyHook)(uint64_t, bool);
KeyHook _KeyHook;

auto KeyHook_Callback(uint64_t key, bool isDown) -> void {
    hookMgr->keyMap[key] = isDown;

    bool cancel = false;
    for(auto category : hookMgr->categories) {
        for(auto mod : category->modules) {
            if(mod->isEnabled)
                mod->onKey(key, isDown, &cancel);
        };
    };

    if(!cancel)
        _KeyHook(key, isDown);
};

auto Manager::initHooks(void) -> void {
    hookMgr = this;
    
    if (kiero::init(kiero::RenderType::D3D12) != kiero::Status::Success)
        return Utils::debugLog("Failed to create hook for SwapChain::Present (DX12)");
    
    kiero::bind(140, (void**)&oPresentD3D12, hookPresentD3D12);
    

    /* Key Hook */
    
    auto sig = Mem::findSig("48 89 5C 24 ? 57 48 83 EC 30 8B 05 ? ? ? ? 8B DA");

    if(!sig)
        return Utils::debugLog("Failed to find Sig for Key Hook");

    if(MH_CreateHook((void*)sig, &KeyHook_Callback, reinterpret_cast<LPVOID*>(&_KeyHook)) != MH_OK)
        return Utils::debugLog("Failed to create hook for Key Hook");
    
    MH_EnableHook((void*)sig);
    
    
    /* Mob Tick Hook */

    sig = Mem::findSig("48 89 5C 24 08 4C 89 44 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 83 EC 60");
    
    if(!sig)
        return Utils::debugLog("Failed to find Sig for Actor_BlockSource");
    
    if(MH_CreateHook((void*)sig, &Actor_BlockSource_Callback, reinterpret_cast<LPVOID*>(&_Actor_BlockSource)) != MH_OK)
        return Utils::debugLog("Failed to create hook for Actor_BlockSource");
    
    MH_EnableHook((void*)sig);

    
    /* GameMode Tick Hook */

    sig = Mem::findSig("48 8D 05 ? ? ? ? 48 8B D9 48 89 01 8B FA 48 8B 89 ? ? ? ? 48 85 C9 74 0A 48 8B 01 BA ? ? ? ? FF 10 48 8B 8B");
    int offset = *reinterpret_cast<int*>(sig + 3);
    uintptr_t** VTable = reinterpret_cast<uintptr_t**>(sig + offset + 7);

    if(!sig || VTable == nullptr)
        return Utils::debugLog("Failed to find Sig for GameMode_Tick");
    
    if(MH_CreateHook((void*)VTable[8], &GameMode_Tick_Callback, reinterpret_cast<LPVOID*>(&_GameMode_Tick)) != MH_OK)
        return Utils::debugLog("Failed to create hook for GameMode_Tick");
    
    MH_EnableHook((void*)VTable[8]);
};

#include "../Module/Modules/Combat/Killaura.h"
#include "../Module/Modules/Combat/Hitbox.h"

#include "../Module/Modules/Movement/AirJump.h"

#include "../Module/Modules/Visuals/TabGui.h"

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
        new Killaura(combat);
        new Hitbox(combat);
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
        new TabGui(visuals);
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