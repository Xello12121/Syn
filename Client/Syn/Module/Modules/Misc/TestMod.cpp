#include "TestMod.h"
#include "../../../Category/Category.h"
#include "../../../Manager/Manager.h"

auto TestModule::onRender(void) -> void {
    RenderUtils::setDrawList(ImGui::GetBackgroundDrawList());

    auto player = MC::getLocalPlayer();
    
    auto instance = MC::getClientInstance();
    auto guiData = (instance != nullptr ? instance->getGuiData() : nullptr);
    auto mcGame = (instance != nullptr ? instance->getMinecraftGame() : nullptr);

    if(guiData == nullptr || mcGame == nullptr)
        return;

    auto res = guiData->res;
    auto fontSize = guiData->scale;
    auto text = std::string(mcGame != nullptr && mcGame->canUseKeys && player != nullptr ? player->getNameTag().c_str() : player != nullptr ? "Menu" : "Main Menu");
    
    auto textRect = RenderUtils::getTextSize(text, fontSize);
    auto textPos = ImVec4(5.f, res.y - textRect.y, 5.f + textRect.x, res.y);

    RenderUtils::fillRect(textPos, ImColor(25.f, 25.f, 25.f, .8f), 0.f);
    RenderUtils::drawText(text, fontSize, ImVec2(textPos.x + 2.f, textPos.y), ImColor(255.f, 255.f, 255.f));
};