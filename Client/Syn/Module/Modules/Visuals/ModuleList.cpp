#include "ModuleList.h"
#include "../../../Category/Category.h"
#include "../../../Manager/Manager.h"

class TextData {
public:
    Module* mod = nullptr;
    float offX = 0.f;
public:
    TextData(Module* mod, float offX) {
        this->mod = mod;
        this->offX = offX;
    };
};

std::vector<TextData*> textData = std::vector<TextData*>();

auto ModuleList::updateAlpha(void) -> void {
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

auto ModuleList::onRender(Renderer* r) -> void {
    this->updateAlpha();

    auto manager = this->category->manager;
    auto categories = manager->categories;

    auto instance = MC::getClientInstance();
    auto guiData = (instance != nullptr ? instance->getGuiData() : nullptr);
    auto res = (guiData != nullptr ? guiData->res : Vec2<float>());

    if(guiData == nullptr)
        return;

    if(textData.empty()) {
        auto moduleNames = std::vector<std::string>();

        for(auto category : categories) {
            for(auto mod : category->modules) {
                moduleNames.push_back(mod->name);
            };
        };

        std::sort(moduleNames.begin(), moduleNames.end(), [](const std::string& a, const std::string& b){
            return (a.size() < b.size());
        });

        for(auto text : moduleNames) {
            for(auto category : categories) {
                for(auto mod : category->modules) {
                    if(mod->name == text)
                        textData.push_back(new TextData(mod, res.x));
                };
            };
        };
    };

    auto I = 0;
    auto textSize = 30.f;
    auto animModifier = 4.f;

    for(auto data : textData) {
        auto mod = data->mod;
        
        auto text = std::wstring(mod->name.begin(), mod->name.end());
        auto height = r->getTextHeight(text, textSize);
        auto width = r->getTextWidth(text, textSize);

        if(data->offX < (res.x - (width + 10.f)) || data->offX > (res.x + width))
            data->offX = (mod->isEnabled ? res.x - width : res.x);

        if(mod->isEnabled) {
            if(data->offX > (res.x - width))
                data->offX -= animModifier;
        } else {
            if(data->offX < res.x)
                data->offX += animModifier;
        };

        if(data->offX >= res.x)
            continue;

        r->fillRectangle(Vec4<float>(data->offX, (I * (height + (textSize / (textSize / 2)))), res.x, (I * (height + (textSize / (textSize / 2)))) + height), Color(21, 21, 21, alpha));
        r->drawRectangle(Vec4<float>(data->offX, (I * (height + (textSize / (textSize / 2)))), res.x, (I * (height + (textSize / (textSize / 2)))) + height), Color(255, 255, 255, alpha), 2);
        r->drawString(text, textSize, Vec2<float>(data->offX, (I * (height + (textSize / (textSize / 2))))), Color(255, 255, 255, alpha));

        I++;
    };
};