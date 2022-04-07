#ifndef CLIENT_SDK_CLASSES_LEVEL
#define CLIENT_SDK_CLASSES_LEVEL

class Actor;

class Level {
private:
    uintptr_t** VTable;
public:
    auto fetchEntity(uint64_t runtimeId, bool paramB) -> Actor* {
        using FetchEntity = Actor* (__thiscall*)(Level*, uint64_t, bool);
        auto _FetchEntity = (FetchEntity)(this->VTable[48]);

        return _FetchEntity(this, runtimeId, paramB);
    };
};

#endif /* CLIENT_SDK_CLASSES_LEVEL */