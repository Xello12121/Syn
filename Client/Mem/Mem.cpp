#include "Mem.h"

auto Mem::findSig(const char* sig, const char* mod) -> uintptr_t {
    const char* pattern = sig;
	uintptr_t firstMatch = 0;
	const uintptr_t rangeStart = (uintptr_t)GetModuleHandleA(mod);
	MODULEINFO miModInfo;
	
    GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
	
    const uintptr_t rangeEnd = rangeStart + miModInfo.SizeOfImage;

    BYTE patByte = GET_BYTE(pattern);
	const char* oldPat = pattern;

    for (uintptr_t pCur = rangeStart; pCur < rangeEnd; pCur++){
        if (!*pattern)
            return firstMatch;
        
        while (*(PBYTE)pattern == ' ')
            pattern++;
        
        if (!*pattern)
            return firstMatch;
        
        if (oldPat != pattern){
            oldPat = pattern;
            if (*(PBYTE)pattern != '\?')
                patByte = GET_BYTE(pattern);
        };

        if (*(PBYTE)pattern == '\?' || *(BYTE*)pCur == patByte){
            if (!firstMatch)
                firstMatch = pCur;
            
            if (!pattern[2])
                return firstMatch;
            
            pattern += 2;
        }
        else {
            pattern = sig;
            firstMatch = 0;
        };
    };
    return NULL;
};

#include "../Utils/Utils.h"

/*auto Mem::findMultiLvlPtr(uintptr_t baseAddr, std::vector<unsigned int> offsets) -> uintptr_t {

    uintptr_t res = baseAddr;
    auto I = 0;
    
    do {
        
        //

    } while(res != NULL && I < offsets.size());

    if(res != NULL) {
        
        std::ostringstream o;
        o << std::hex << res << std::endl;

        Utils::debugLog(o.str());

    };

    return (res != baseAddr ? res : NULL);
};*/

/*auto Mem::findMultiLvlPtr(uintptr_t baseAddr, std::vector<unsigned int> offsets) -> uintptr_t {
    
    auto hwnd = GetModuleHandleA("Minecraft.Windows.exe");
    auto addr = (uintptr_t)(hwnd) + baseAddr;
    auto I = 0;

    if(hwnd == NULL)
        return 0;
    
    do {
        
        auto currRes = reinterpret_cast<uintptr_t*>((uintptr_t)(addr) + offsets[I]);

        if(currRes == nullptr) {
            return 0;
        };
        
        addr = *(uintptr_t*)(addr) + (uintptr_t)offsets[I];
        I++;

    } while(I < offsets.size());

    return addr;
};*/

auto Mem::findMultiLvlPtr(uintptr_t baseAddr, std::vector<unsigned int> offsets) -> uintptr_t* {

    auto hwnd = GetModuleHandleA("Minecraft.Windows.exe");

    if(hwnd == NULL)
        return nullptr;
    
    auto ptr = (uintptr_t)(hwnd) + baseAddr;
    auto I = 0;

    do {

        ptr = *(uintptr_t*)ptr;

        if(ptr == NULL)
            return nullptr;
        
        ptr += offsets[I];

        if(ptr == NULL)
            return nullptr;
        
        I++;

    } while(I < offsets.size());

    return ((I >= offsets.size()) ? (uintptr_t*)ptr : nullptr);
};