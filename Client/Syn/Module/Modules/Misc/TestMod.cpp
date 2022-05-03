#include "TestMod.h"
#include "../../../Category/Category.h"
#include "../../../Manager/Manager.h"

auto TestModule::onRender(void) -> void {
    ImGui::Begin(std::string("Test Module").c_str());

    if(!this->updatedWindowSize) {
        ImGui::SetWindowSize(ImVec2(600.f, 600.f));
        this->updatedWindowSize = true;
    };
    
    auto manager = this->category->manager;
    
    for(auto category : manager->categories) {
        
        ImGui::Spacing();
        ImGui::Spacing();

        if(ImGui::TreeNode(category->name.c_str())) {
            
            for(auto mod : category->modules) {
                
                ImGui::Spacing();

                if(ImGui::TreeNode(mod->name.c_str())) {

                    ImGui::Text(std::string("Name: " + mod->name).c_str());
                    ImGui::Text(std::string("Category: " + category->name).c_str());
                    ImGui::Text(std::string("Is Enabled: " + std::string(mod->isEnabled ? "True" : "False")).c_str());

                    if(ImGui::Button(std::string(mod->isEnabled ? "Disable" : "Enable").c_str())) {
                        mod->isEnabled = !mod->isEnabled;
                    };
                    
                    ImGui::TreePop();

                };

            };

            ImGui::TreePop();

        };

    };

    ImGui::End();
};

auto TestModule::onEnable(void) -> void {
    this->updatedWindowSize = false;
};

auto TestModule::onDisable(void) -> void {
    this->isEnabled = true;
};