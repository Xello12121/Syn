#include "TestMod.h"
#include "../../../Category/Category.h"
#include "../../../Manager/Manager.h"

auto TestModule::onRender(void) -> void {
    ImGui::Begin(std::string("Test Console").c_str());

    if(!this->updatedWindowSize) {
        ImGui::SetWindowSize(ImVec2(600.f, 600.f));
        this->updatedWindowSize = true;
    };

    if(ImGui::CollapsingHeader(std::string("Entity List").c_str())) {
        for(auto [runtimeId, entity] : this->category->manager->entityMap) {
            ImGui::Text(std::to_string(runtimeId).c_str());
        };
    };

    ImGui::End();
};

auto TestModule::onEnable(void) -> void {
    this->updatedWindowSize = false;
};