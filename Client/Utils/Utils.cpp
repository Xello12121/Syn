#include "Utils.h"

auto Utils::GetDll(void) -> HMODULE {
    MEMORY_BASIC_INFORMATION info;
    size_t len = VirtualQueryEx(GetCurrentProcess(), (void*)GetDll, &info, sizeof(info));
    assert(len == sizeof(info));
    return len ? (HMODULE)info.AllocationBase : NULL;
};

auto Utils::getDebugDir(void) -> std::string {
    char* path = NULL;
    size_t length;

    _dupenv_s(&path, &length, "appdata");

    return std::string(path);
};

auto Utils::debugLog(std::string output) -> void {
    static bool init = false;
    static auto path = std::string(getDebugDir() + "\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState");

    auto file = std::string(path + "\\Output.txt");
    
    if(!init) {
        auto f = std::filesystem::path(file);

        if(std::filesystem::exists(f))
            std::filesystem::remove(f);
        
        init = true;
    };
    
    CloseHandle(CreateFileA(file.c_str(), GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL));

    std::ofstream fStream;
    fStream.open(file.c_str(), std::ios::app);
    
    if(fStream.is_open())
        fStream << output << "\n" << std::endl;
    
    return fStream.close();
};

/* Draw Utils */

ImDrawList* RenderUtils::draw = nullptr;

auto RenderUtils::setDrawList(ImDrawList* draw) -> void {
    RenderUtils::draw = draw;
};

auto RenderUtils::getDrawList(void) -> ImDrawList* {
    return RenderUtils::draw;
};

auto RenderUtils::getTextSize(std::string text, float fontSize) -> ImVec2 {
    auto font = ImGui::GetFont();
    return font->CalcTextSizeA(fontSize * 10.f, 1000.f, -1.f, text.c_str());
};

auto RenderUtils::drawText(std::string text, float fontSize, ImVec2 pos, ImColor col) -> void {
    if(RenderUtils::draw == nullptr)
        return;
    draw->AddText(ImGui::GetFont(), fontSize * 10.f, pos, ImColor(col.Value.x / 255.f, col.Value.y / 255.f, col.Value.z / 255.f, col.Value.w), text.c_str());
};

auto RenderUtils::fillRect(ImVec4 pos, ImColor col, float round) -> void {
    if(RenderUtils::draw == nullptr)
        return;
    
    draw->AddRectFilled(ImVec2(pos.x, pos.y), ImVec2(pos.z, pos.w), ImColor(col.Value.x / 255.f, col.Value.y / 255.f, col.Value.z / 255.f, col.Value.w), round);
};