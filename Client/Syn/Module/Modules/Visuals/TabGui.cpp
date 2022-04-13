#include "TabGui.h"
#include "../../../Category/Category.h"
#include "../../../Manager/Manager.h"

auto TabGui::updateAlpha(void) -> void {
    auto instance = MC::getClientInstance();
    auto mcGame = (instance != nullptr ? instance->getMinecraftGame() : nullptr);

    auto modifier = 0.05f;

    if(mcGame == nullptr || !mcGame->canUseKeys) {
        if(alpha > 0.f)
            alpha -= modifier;
    } else {
        if(alpha < 1.f)
            alpha += modifier;
    };
};

auto TabGui::onRender(Renderer* r) -> void {
    auto manager = this->category->manager;
    
    auto categories = manager->categories;
    auto modules = categories.at(selCatIndex)->modules;

    this->updateAlpha();

    auto yOff = 0.f;
    auto rectWidth = 0;
    auto textSize = 23.f;
    
    for(auto category : categories) {
        auto name = std::wstring(category->name.begin(), category->name.end());
        auto height = r->getTextHeight(name, textSize);
        
        yOff += height;

        auto currWidth = r->getTextWidth(name, textSize);

        if(currWidth > rectWidth)
            rectWidth = currWidth;
    };

    auto rectPos = Vec4<float>(4.f, 6.f, 16.f + rectWidth, yOff + 14.f);
    
    r->fillRectangle(rectPos, Color(21, 21, 21, alpha));
    r->drawRectangle(rectPos, Color(255, 255, 255, alpha), 2);

    auto I = 0;
    for(auto category : categories) {
        auto name = std::wstring(category->name.begin(), category->name.end());
        auto height = r->getTextHeight(name, textSize);

        if(selectedCat && selCatIndex == I) {
            if(selCatAnimModifier == 0.f)
                selCatAnimModifier = 8.f;
            
            if(selCatAnimModifier < (rectPos.z - 4.f))
                selCatAnimModifier += animSpeedModifier;

            r->fillRectangle(Vec4<float>(8.f, (I * height) + 9.f, selCatAnimModifier, ((I * height) + 9.f) + height), Color(3, 194, 252, alpha));
        };
        
        r->drawString(name, textSize, Vec2<float>(10.f, (I * height) + 10.f), Color(255, 255, 255, alpha));

        I++;
    };

    if(modules.empty() || !selectedCat)
        return;

    rectWidth = 0.f;
    yOff = 0.f;
    for(auto mod : modules) {
        auto name = std::wstring(mod->name.begin(), mod->name.end());
        auto height = r->getTextHeight(name, textSize);

        yOff += height;

        auto currWidth = r->getTextWidth(name, textSize);

        if(currWidth > rectWidth)
            rectWidth = currWidth;
    };

    rectPos = Vec4<float>(rectPos.z, rectPos.y, rectPos.z + (16.f + rectWidth), rectPos.y + (yOff + 9.f));
    
    r->fillRectangle(rectPos, Color(21, 21, 21, alpha));
    r->drawRectangle(rectPos, Color(255, 255, 255, alpha), 2);

    I = 0;
    for(auto mod : modules) {
        auto name = std::wstring(mod->name.begin(), mod->name.end());
        auto height = r->getTextHeight(name, textSize);

        if(selectedMod && selModIndex == I) {
            if(selModAnimModifier == 0.f)
                selModAnimModifier = rectPos.x + 6.f;
            
            if(selModAnimModifier < (rectPos.z - 6.f))
                selModAnimModifier += animSpeedModifier;

            r->fillRectangle(Vec4<float>(rectPos.x + 6.f, (I * height) + 10.f, selModAnimModifier, ((I * height) + 10.f) + height), Color(3, 194, 252, alpha));
        };

        r->drawString(name, textSize, Vec2<float>(rectPos.x + 8.f, rectPos.y + (I * height) + 4.f), mod->isEnabled ? Color(25, 225, 150, alpha) : Color(255, 255, 255, alpha));
        I++;
    };
};

auto TabGui::onKey(uint64_t key, bool isDown, bool* cancel) -> void {
    auto instance = MC::getClientInstance();
    auto mcGame = (instance != nullptr ? instance->getMinecraftGame() : nullptr);

    if(mcGame == nullptr || !mcGame->canUseKeys)
        return;
    
    if(!isDown || key < 0x25 || key > 0x28)
        return;
    
    auto categories = this->category->manager->categories;
    auto modules = categories.at(selCatIndex)->modules;
    
    switch(key) {
        case VK_RIGHT:
            if(!selectedCat) {
                selectedCat = true;
            } else {
                if(!selectedMod) {
                    selectedMod = true;
                } else {
                    auto mod = modules.at(selModIndex);

                    if(mod == nullptr)
                        return;
                    
                    mod->isEnabled = !mod->isEnabled;
                    selModAnimModifier = 0.f;
                };
            };
        break;
        case VK_LEFT:
            if(selectedMod) {
                selectedMod = false;
                selModAnimModifier = 0.f;
            } else {
                selectedCat = false;
                selCatAnimModifier = 0.f;
            };
        break;
        case VK_UP:
            if(!selectedMod) {
                selCatIndex--;
                selCatAnimModifier = 0.f;

                if(selCatIndex < 0)
                    selCatIndex = (categories.size() - 1);
            } else {
                selModIndex--;
                selModAnimModifier = 0.f;

                if(selModIndex < 0)
                    selModIndex = (modules.size() - 1);
            }
        break;
        case VK_DOWN:
            if(!selectedMod) {
                selCatIndex++;
                selCatAnimModifier = 0.f;

                if(selCatIndex > (categories.size() - 1))
                    selCatIndex = 0;
            } else {
                selModIndex++;
                selModAnimModifier = 0.f;
                
                if(selModIndex > (modules.size() - 1))
                    selModIndex = 0;
            };
        break;
    };

    *cancel = true;
};