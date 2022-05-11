#include "Nuker.h"

auto Nuker::onStartDestroyBlock(GameMode* GM, Vec3<int>* blockPos, uint8_t blockFace, bool* p3) -> void {
    
    for(auto x = -range; x < range; x++) {
        for(auto y = -range; y < range; y++) {
            for(auto z = -range; z < range; z++) {
                
                auto currPos = Vec3<int>(blockPos->x + x, blockPos->y + y, blockPos->z + z);
                GM->destroyBlock(&currPos, blockFace);

            };
        };
    };

};

auto Nuker::onContinueDestroyBlock(GameMode* GM, Vec3<int>* blockPos, uint8_t blockFace, Vec3<float>* p3, bool* p4) -> void {

    this->onStartDestroyBlock(GM, blockPos, blockFace, p4);

};

auto Nuker::onRenderOptions(void) -> void {

    ImGui::SliderInt(std::string("Range").c_str(), &range, 1, 8);

};