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

auto Mem::findMultiLvlPtr(uintptr_t baseAddr, std::vector<unsigned int> offsets) -> uintptr_t {
    uintptr_t addr = baseAddr;
    
    for (int I = 0; I < offsets.size(); I++){
        addr = *(uintptr_t*)(addr);
        if ((uintptr_t*)(addr) == nullptr)
            return addr;
        addr += offsets[I];
    };

    return addr;
};