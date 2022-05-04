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

    auto player = MC::getLocalPlayer();

    if(player != nullptr) {
        if(ImGui::TreeNode(std::string("Player").c_str())) {
            
            if(ImGui::TreeNode(std::string("Position").c_str())) {
                
                auto pos = *player->getPos();
                
                ImGui::Text(std::string("X: " + std::to_string(pos.x)).c_str());
                ImGui::Text(std::string("Y: " + std::to_string(pos.y)).c_str());
                ImGui::Text(std::string("Z: " + std::to_string(pos.z)).c_str());

                ImGui::TreePop();

            };

            if(ImGui::TreeNode(std::string("Properties").c_str())) {

                ImGui::Text(std::string("On Ground: " + std::string(player->onGround ? "True" : "False")).c_str());
                ImGui::Text(std::string("Is Jumping: " + std::string(player->isJumping() ? "True" : "False")).c_str());
                
                if(ImGui::Button(std::string("Boost").c_str())) {
                    
                    auto lerpTo = Vec3(0.f, 1.f, 0.f);
                    player->lerpMotion(&lerpTo);

                };

                if(ImGui::Button(std::string("Swing Arm").c_str())) {
                    
                    player->swing();

                };

                ImGui::TreePop();

            };

            ImGui::TreePop();

        };
    };
    
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