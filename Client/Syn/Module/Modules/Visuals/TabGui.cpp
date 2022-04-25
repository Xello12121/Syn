#include "TabGui.h"
#include "../../../Category/Category.h"
#include "../../../Manager/Manager.h"

auto TabGui::updateAlpha(void) -> void {
    auto instance = MC::getClientInstance();
    auto mcGame = (instance != nullptr ? instance->getMinecraftGame() : nullptr);

    auto modifier = this->animModifier;

    if(mcGame != nullptr && mcGame->canUseKeys)
        alpha += (alpha < 1.f ? modifier : 0.f);
    else
        alpha -= (alpha > 0.f ? modifier : 0.f);
};

auto TabGui::getScale(void) -> float {
    auto instance = MC::getClientInstance();
    auto guiData = (instance != nullptr ? instance->getGuiData() : nullptr);

    return (guiData != nullptr ? guiData->scale : 3.f);
};

auto TabGui::onRender(void) -> void {
    this->updateAlpha();

    auto manager = this->category->manager;
    auto categories = manager->categories;
    
    auto modules = categories.at(selCatIndex)->modules;

    auto I = 0;
    auto cRectLen = 0.f;
    auto fontSize = this->getScale();

    this->alpha = 1.f;

    RenderUtils::setDrawList(ImGui::GetForegroundDrawList());

    for(auto category : categories) {
        auto calcSize = RenderUtils::getTextSize(category->name, fontSize);

        auto textPos = ImVec2(10.f, I * (fontSize * 10.f) + 10.f);
        RenderUtils::drawText(category->name, fontSize, textPos, ImColor(255.f, 255.f, 255.f, alpha));

        if(calcSize.x > cRectLen)
            cRectLen = calcSize.x;

        I++;
    };

    RenderUtils::setDrawList(ImGui::GetBackgroundDrawList());
    RenderUtils::fillRect(ImVec4(4.f, 10.f, 10.f + cRectLen, categories.size() * (fontSize * 10.f) + 10.f), ImColor(21.f, 21.f, 21.f, alpha), 5.f);

    if(this->selectedCat) {
        auto calcSize = RenderUtils::getTextSize(categories.at(selCatIndex)->name, fontSize);
        auto targetXOff = 10.f + cRectLen;

        if(selCatAnimOff < (targetXOff))
            selCatAnimOff += 5.f;
        
        if(selCatAnimOff > (targetXOff))
            selCatAnimOff = targetXOff;

        RenderUtils::fillRect(ImVec4(5.f, selCatIndex * (fontSize * 10.f) + 10.f, selCatAnimOff, (selCatIndex * (fontSize * 10.f) + calcSize.y) + 10.f), ImColor(32.f, 107.f, 227.f, alpha), 5.f);

        I = 0;
        auto mRectLen = 0.f;

        RenderUtils::setDrawList(ImGui::GetForegroundDrawList());

        for(auto mod : modules) {
            auto calcSize = RenderUtils::getTextSize(mod->name, fontSize);
            
            auto textPos = ImVec2(12.f + cRectLen, I * (fontSize * 10.f) + 10.f);
            RenderUtils::drawText(mod->name, fontSize, textPos, mod->isEnabled ? ImColor(50.f, 168.f, 82.f, alpha) : ImColor(255.f, 255.f, 255.f, alpha));

            if(calcSize.x > mRectLen)
                mRectLen = calcSize.x;
            
            I++;
        };

        RenderUtils::setDrawList(ImGui::GetBackgroundDrawList());
        RenderUtils::fillRect(ImVec4(12.f + cRectLen, 10.f, (12.f + cRectLen) + mRectLen, modules.size() * (fontSize * 10.f) + 10.f), ImColor(21.f, 21.f, 21.f, alpha), 5.f);

        if(this->selectedMod) {
            auto calcSize = RenderUtils::getTextSize(modules.at(selModIndex)->name, fontSize);
            auto targetXOff = (12.f + cRectLen) + mRectLen;

            if(selModAnimOff < (targetXOff)) {
                if(selModAnimOff <= 0.f)
                    selModAnimOff = 12.f + cRectLen;
                
                selModAnimOff += 5.f;
            };
            
            if(selModAnimOff > (targetXOff))
                selModAnimOff = targetXOff;

            RenderUtils::fillRect(ImVec4(12.f + cRectLen, selModIndex * (fontSize * 10.f) + 10.f, selModAnimOff, (selModIndex * (fontSize * 10.f) + calcSize.y) + 10.f), ImColor(32.f, 107.f, 227.f, alpha), 5.f);
        };
    };
};

auto TabGui::onKey(uint64_t key, bool isDown, bool* cancel) -> void {
    auto instance = MC::getClientInstance();
    auto mcGame = (instance != nullptr ? instance->getMinecraftGame() : nullptr);

    if(mcGame == nullptr || !mcGame->canUseKeys)
        return;
    
    if(!isDown || key < 0x25 || key > 0x28)
        return;
    
    auto manager = this->category->manager;
    auto categories = manager->categories;

    auto selCat = categories.at(this->selCatIndex);
    auto selMods = (selCat != nullptr ? selCat->modules : std::vector<Module*>());

    switch(key) {
        
        case VK_RIGHT:
            if(!this->selectedCat) {
                this->selectedCat = true;
            } else {
                if(!this->selectedMod) {
                    this->selectedMod = true;
                } else {
                    auto mod = selMods.at(this->selModIndex);

                    if(mod != nullptr)
                        mod->isEnabled = !mod->isEnabled;
                };
            };
        break;
        
        case VK_LEFT:
            if(this->selectedMod) {
                this->selectedMod = false;
                this->selModAnimOff = 0.f;
                this->selModIndex = 0;
            } else {
                if(this->selectedCat) {
                    this->selectedCat = false;
                    this->selCatAnimOff = 0.f;
                    this->selCatIndex = 0;
                };
            };
        break;

        case VK_UP:
            if(this->selectedCat && !this->selectedMod) {
                
                if(selCatIndex <= 0)
                    this->selCatIndex = categories.size();
                
                this->selCatIndex--;
                this->selCatAnimOff = 0.f;
                
            } else if(this->selectedMod) {
                
                if(this->selModIndex <= 0)
                    this->selModIndex = selMods.size();
                
                this->selModIndex--;
                this->selModAnimOff = 0.f;

            };
        break;

        case VK_DOWN:
            if(this->selectedCat && !this->selectedMod) {
                
                this->selCatIndex++;
                this->selCatAnimOff = 0.f;

                if(this->selCatIndex >= categories.size())
                    this->selCatIndex = 0;
                
            } else if(this->selectedMod) {
                this->selModIndex++;
                this->selModAnimOff = 0.f;

                if(this->selModIndex >= selMods.size())
                    this->selModIndex = 0;
            };
        break;

        *cancel = true;
    
    };
};