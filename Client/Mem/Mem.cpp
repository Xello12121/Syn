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

auto Mem::findMultiLvlPtr(uintptr_t baseAddr, std::vector<unsigned int> offsets) -> uintptr_t* {

    auto hwnd = GetModuleHandle("Minecraft.Windows.exe");
    
    auto ptr = (uintptr_t)(hwnd) + baseAddr;
    auto i = 0;

    do {

        if(*(uintptr_t*)ptr + offsets[i] == offsets[i] || *(uintptr_t*)ptr + offsets[i] > 0xFFFFFFFFFFFF)
            break;
        
        ptr = *(uintptr_t*)ptr + offsets[i];

        if(ptr == NULL)
            break;
        
        i++;

    } while(i < offsets.size());

    //Utils::debugLog(std::to_string(i) + " | " + std::to_string(offsets.size()));
    
    return (i == offsets.size() ? (uintptr_t*)ptr : nullptr);
};