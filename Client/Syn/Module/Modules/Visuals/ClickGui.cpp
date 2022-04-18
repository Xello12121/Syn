#include "ClickGui.h"

auto ClickGui::onEnable(void) -> void {
    ImGui::SetNextWindowSize(ImVec2(300.f, 300.f));
};

auto ClickGui::onRender(void) -> void {
    ImGui::Begin("Click Gui", &this->isEnabled);
    ImGui::SetWindowCollapsed(false);

    ImGui::End();
};