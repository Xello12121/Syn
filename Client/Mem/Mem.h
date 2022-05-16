#ifndef CLIENT_MEM_MEM
#define CLIENT_MEM_MEM

#include <Windows.h>
#include <MinHook.h>
#include <Psapi.h>
#include <vector>

#include "../../Includes/kiero/kiero.h"

#define INRANGE(x,a,b) (x >= a && x <= b)
#define GET_BYTE( x )  (GET_BITS(x[0]) << 4 | GET_BITS(x[1]))
#define GET_BITS( x )  (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))

class Mem {
public:
    static auto findSig(const char* sig, const char* mod = "Minecraft.Windows.exe") -> uintptr_t;
    static auto findMultiLvlPtr(uintptr_t baseAddr, std::vector<unsigned int> offsets) -> uintptr_t*;
public:
    template<typename T, typename... Args>
    static auto fastCall(void* func, Args... args) -> T {
        using F = T (__fastcall*)(Args...);
        auto _F = (F)func;

        return _F(args...);
    };
};

#endif /* CLIENT_MEM_MEM */