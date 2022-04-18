#include "ClickGui.h"
#include "../../../Category/Category.h"
#include "../../../Manager/Manager.h"

auto ClickGui::onRender(void) -> void {
    ImGui::Begin("Click Gui", &this->isEnabled);

    if(this->setSize) {
        ImGui::SetWindowSize(ImVec2(300.f, 300.f));
        this->setSize = false;
    };

    for(auto category : this->category->manager->categories) {
        
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        if(ImGui::CollapsingHeader(category->name.c_str())) {

            ImGui::Spacing();
            ImGui::Spacing();
            
            for(auto mod : category->modules) {

                ImGui::Spacing();

                if(ImGui::CollapsingHeader(mod->name.c_str())) {

                    ImGui::Spacing();
                    ImGui::Button(mod->name.c_str());
                
                };
            };
        };
    };

    ImGui::End();
};