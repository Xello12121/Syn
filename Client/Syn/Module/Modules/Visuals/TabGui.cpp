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
    
    auto I = 0;
    auto fontSize = 3.f;

    for(auto category : this->category->manager->categories) {
        auto textRect = RenderUtils::getTextSize(category->name, 3.f);
        auto textPos = ImVec4(8.f, 8.f + I * (fontSize * 10), 12.f + textRect.x, (12.f + I * (fontSize * 10)) + textRect.y);

        RenderUtils::fillRect(textPos, ImColor(0.2f, 0.2f, 0.2f), 0.f);
        RenderUtils::drawText(category->name, 3.f, ImVec2(textPos.x, textPos.y), ImColor(255, 255, 255));

        I++;
    };

};