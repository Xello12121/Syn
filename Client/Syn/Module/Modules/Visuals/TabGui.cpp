#include "TabGui.h"
#include "../../../Category/Category.h"
#include "../../../Manager/Manager.h"

auto renderText(ImDrawList* draw, std::string text, float fontSize, ImVec2 pos, ImColor color) -> void {

    auto font = ImGui::GetFont();
    font->Scale = fontSize;
    auto len = 0.f;

    auto c = text.c_str();
    draw->AddText(font, fontSize * 10.f, pos, color, c);
};

auto TabGui::onRender(void) -> void {

    RenderUtils::setDrawList(ImGui::GetBackgroundDrawList());

    auto player = MC::getLocalPlayer();
    auto instance = MC::getClientInstance();
    auto mcGame = (instance != nullptr ? instance->getMinecraftGame() : nullptr);

    auto fontSize = 3.f;
    auto text = std::string(mcGame != nullptr && mcGame->canUseKeys && player != nullptr ? player->getNameTag().c_str() : player != nullptr ? "Menu" : "Main Menu");
    
    auto textRect = RenderUtils::getTextSize(text, fontSize);
    auto textPos = ImVec4(8.f, 8.f + (fontSize * 10.f), 12.f + textRect.x, (12.f + (fontSize * 10.f) + textRect.y));

    RenderUtils::fillRect(textPos, ImColor(25.f, 25.f, 25.f, .8f), 0.f);
    RenderUtils::drawText(text, fontSize, ImVec2(textPos.x + 2.f, textPos.y), ImColor(255.f, 255.f, 255.f));

};