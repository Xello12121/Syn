#include "TestMod.h"
#include "../../../Category/Category.h"
#include "../../../Manager/Manager.h"

auto TestModule::onTick(void) -> void {
    auto entities = this->category->manager->entityMap;

    if(entities.empty())
        return;

    Utils::debugLog(std::string("Entities: " + std::to_string(entities.size())));
};