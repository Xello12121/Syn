#ifndef CLIENT_SDK_CLASSES_GAMEMODE
#define CLIENT_SDK_CLASSES_GAMEMODE

class Player;

class GameMode {
public:
    Player* player;
private:
    virtual ~GameMode();
public:
    virtual auto startDestroyBlock(Vec3<int>*, uint8_t, bool*) -> bool;
    virtual auto destroyBlock(Vec3<int>*, uint8_t) -> bool;
    virtual auto continueDestroyBlock(Vec3<int>*, uint8_t, Vec3<float>*, bool*) -> bool;
    virtual auto stopDestroyBlock(Vec3<int>*) -> void;
    virtual auto startBuildBlock(Vec3<int>*, uint8_t) -> void;
    virtual auto buildBlock(Vec3<int>*, uint8_t, bool*) -> bool;
    virtual auto continueBuildBlock(Vec3<int>*, uint8_t) -> void;
    virtual auto stopBuildBlock(void) -> void;
    virtual auto tick(void) -> void;
    virtual auto getPickRange(int*, bool) -> float;
    virtual auto useItem(uintptr_t*) -> bool;
    virtual auto useItemOn(uintptr_t*, Vec3<int>*, uint8_t, Vec3<float>*, uintptr_t*) -> bool;
    virtual auto interact(Actor*, Vec3<float>*) -> bool;
    virtual auto attack(Actor*) -> bool;
    virtual auto releaseUsingItem(void) -> void;
public:
    auto _creativeDestroyBlock(Vec3<int>* blockPos, uint8_t blockFace) -> void {
        using CreativeDestroyBlock = void (__thiscall*)(GameMode*, Vec3<int>*, uint8_t);
        static auto _CreativeDestroyBlock = (CreativeDestroyBlock)nullptr;

        if(_CreativeDestroyBlock == nullptr)
            _CreativeDestroyBlock = (CreativeDestroyBlock)(Mem::findSig("40 53 56 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 41 ? ? ? 48 8B FA"));

        if(_CreativeDestroyBlock != nullptr)
            _CreativeDestroyBlock(this, blockPos, blockFace);
    };
};

#endif /* CLIENT_SDK_CLASSES_GAMEMODE */