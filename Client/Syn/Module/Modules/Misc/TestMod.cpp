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
    auto myPos = (player != nullptr ? *player->getPos() : Vec3<float>());

    if(player != nullptr && ImGui::TreeNode(std::string("Local Player").c_str())) {

        if(ImGui::TreeNode(std::string("Position").c_str())) {
            
            auto pos = *player->getPos();
            
            ImGui::Text(std::string("X: " + std::to_string((int)pos.x)).c_str());
            ImGui::Text(std::string("Y: " + std::to_string((int)(pos.y - 2.f))).c_str());
            ImGui::Text(std::string("Z: " + std::to_string((int)pos.z)).c_str());

            ImGui::TreePop();

        };

        if(ImGui::TreeNode(std::string("Properties").c_str())) {

            ImGui::Text(std::string("On Ground: " + std::string(player->onGround ? "True" : "False")).c_str());
            ImGui::Text(std::string("Is Jumping: " + std::string(player->isJumping() ? "True" : "False")).c_str());
            ImGui::Text(std::string("Is Sleeping: " + std::string(player->isSleeping() ? "True" : "False")).c_str());
            ImGui::Text(std::string("Username: " + std::string(player->getNameTag().c_str())).c_str());
            
            if(ImGui::Button(std::string("Y-Shift").c_str())) {
                
                auto pos = *player->getPos();
                pos.y += 5.f;

                player->setPos(&pos);

            };
            
            if(ImGui::Button(std::string("Boost").c_str())) {
                
                auto lerpTo = Vec3(0.f, 1.f, 0.f);
                player->lerpMotion(&lerpTo);

            };

            if(ImGui::Button(std::string("Jump").c_str())) {
                
                player->ascendBlockByJumping();

            };

            if(ImGui::Button(std::string("Swing Arm").c_str())) {
                
                player->swing();

            };

            static bool swimming = false;

            if(ImGui::Button(std::string(std::string(swimming ? "Stop" : "Start") + " Swimming").c_str())) {
                swimming = !swimming;

                if(!swimming)
                    player->stopSwimming();
            };

            if(swimming)
                player->startSwimming();

            ImGui::TreePop();

        };

        ImGui::TreePop();

    };

    auto entityMap = this->category->manager->entityMap;

    if(player != nullptr && entityMap.size() > 1 && ImGui::TreeNode(std::string("Entity Map").c_str())) {
        auto players = std::map<uint64_t, Actor*>();
        
        auto hostiles = std::map<uint64_t, Actor*>();
        auto passives = std::map<uint64_t, Actor*>();

        auto others = std::map<uint64_t, Actor*>();

        auto showEntityPosTree = [&](uint64_t runtimeId, Actor* entity) {
            
            if(ImGui::TreeNode(std::string("Position").c_str())) {
            
                auto pos = *entity->getPos();
                
                ImGui::Text(std::string("X: " + std::to_string((int)pos.x)).c_str());
                ImGui::Text(std::string("Y: " + std::to_string((int)(pos.y - 2.f))).c_str());
                ImGui::Text(std::string("Z: " + std::to_string((int)pos.z)).c_str());

                auto dX = (myPos.x - pos.x);
                auto dY = (myPos.y - pos.y);
                auto dZ = (myPos.z - pos.z);

                auto dist = sqrt(dX * dX + dY * dY + dZ * dZ);

                ImGui::Text(std::string("Distance: " + std::to_string((int)dist)).c_str());

                ImGui::TreePop();

            };

        };

        auto displayMobTree = [&](uint64_t runtimeId, Actor* entity) {
            
            if(ImGui::TreeNode(std::to_string(runtimeId).c_str())) {
                
                ImGui::Text(std::string("Runtime ID: " + std::to_string(runtimeId)).c_str());
                ImGui::Text(std::string("On Ground: " + std::string(entity->onGround ? "True" : "False")).c_str());
                ImGui::Text(std::string("Is Jumping: " + std::string(entity->isJumping() ? "True" : "False")).c_str());
                ImGui::Text(std::string("Is Sleeping: " + std::string(entity->isSleeping() ? "True" : "False")).c_str());

                if(entity->getEntityTypeId() == EntityType::Client_Player)
                    ImGui::Text(std::string("Username: " + std::string(entity->getNameTag().c_str())).c_str());
                
                showEntityPosTree(runtimeId, entity);

                ImGui::TreePop();

            };

        };

        auto displayOtherTree = [&](uint64_t runtimeId, Actor* entity) {
            
            if(ImGui::TreeNode(std::to_string(runtimeId).c_str())) {
                
                ImGui::Text(std::string("Runtime ID: " + std::to_string(runtimeId)).c_str());
                ImGui::Text(std::string("On Ground: " + std::to_string(entity->onGround)).c_str());

                showEntityPosTree(runtimeId, entity);

                ImGui::TreePop();

            };

        };

        for(auto [runtimeId, entity] : entityMap) {
            
            if(runtimeId == player->runtimeId)
                continue;
            
            if(entity->isNotMob()) {
                others[runtimeId] = entity;
                continue;
            };

            if(entity->getEntityTypeId() == EntityType::Client_Player) {
                players[runtimeId] = entity;
                continue;
            };

            if(entity->isHostileType()) {
                hostiles[runtimeId] = entity;
            } else {
                passives[runtimeId] = entity;
            };

        };

        if(players.size() > 0 && ImGui::TreeNode(std::string("Players").c_str())) {
            
            
            for(auto [runtimeId, entity] : players) {
                
                displayMobTree(runtimeId, entity);

            };

            ImGui::TreePop();

        };

        if((hostiles.size() > 0 || passives.size() > 0) && ImGui::TreeNode(std::string("Mobs").c_str())) {
            
            
            if(passives.size() > 0) {
                
                for(auto [runtimeId, entity] : passives) {
                
                    displayMobTree(runtimeId, entity);

                };

            };

            if(hostiles.size() > 0) {
                
                for(auto [runtimeId, entity] : hostiles) {
                
                    displayMobTree(runtimeId, entity);

                };
                
            };

            ImGui::TreePop();

        };

        if(others.size() > 0 && ImGui::TreeNode(std::string("Others").c_str())) {
            
            
            for(auto [runtimeId, entity] : others) {
            
                displayOtherTree(runtimeId, entity);

            };

            ImGui::TreePop();

        };

        ImGui::TreePop();

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

                    if(ImGui::TreeNode(std::string("Options").c_str())) {

                        mod->onRenderOptions();

                        ImGui::TreePop();

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

    ImGuiStyle* style = &ImGui::GetStyle();
 
	style->WindowPadding = ImVec2(15, 15);
	style->WindowRounding = 5.0f;
	style->FramePadding = ImVec2(5, 5);
	style->FrameRounding = 4.0f;
	style->ItemSpacing = ImVec2(12, 4);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 9.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 3.0f;
 
	style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
};

auto TestModule::onDisable(void) -> void {
    this->isEnabled = true;
};