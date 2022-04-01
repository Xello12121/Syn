#include "Client/Client.h"

auto init(HINSTANCE hInstance) -> void {
    new Client("Syn");
};

auto DllMain(HINSTANCE hInstance, DWORD fdwReason, LPVOID lpRes) -> BOOL {
    
    switch(fdwReason) {
        case DLL_PROCESS_ATTACH:
            CreateThread(0, 0, (LPTHREAD_START_ROUTINE)init, hInstance, 0, 0);
        break;
    };
    
    return TRUE;
};