#include "TestMod.h"
#include "../../../Category/Category.h"
#include "../../../Manager/Manager.h"

auto TestModule::onRender(void) -> void {
    ImGui::Begin(std::string("Test Module").c_str());

    if(!this->updatedWindowSize) {
        ImGui::SetWindowSize(ImVec2(600.f, 600.f));
        this->updatedWindowSize = true;
    };

    auto player = MC::getLocalPlayer();
    
    if(ImGui::TreeNode(std::string("Entity Map").c_str())) {
            
        for(auto [runtimeId, entity] : category->manager->entityMap) {

            ImGui::Spacing();
            
            if(ImGui::TreeNode(std::to_string(runtimeId).c_str())) {
                
                ImGui::Text(std::string("ID: " + std::to_string(runtimeId)).c_str());

                if(ImGui::TreeNode(std::string("Options").c_str())) {
                    
                    if(ImGui::Button(std::string("Boost").c_str())) {
                        
                        auto lerpTo = Vec3(0.f, 1.f, 0.f);
                        entity->lerpMotion(&lerpTo);

                    };

                    ImGui::TreePop();

                };

                ImGui::TreePop();

            };

            ImGui::Spacing();

        };

        ImGui::TreePop();

    };


    ImGui::End();
};

auto TestModule::onEnable(void) -> void {
    this->updatedWindowSize = false;
};