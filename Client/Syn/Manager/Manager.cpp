#include "Manager.h"

#include "../Category/Category.h"
#include "../Module/Module.h"

Manager::Manager(Client* client) {
    this->client = client;
    this->init();
};

#include "../Module/Modules/Movement/AirJump.h"

auto Manager::init(void) -> void {
    if(this->categories.empty()) {
        auto names = { "Combat", "Movement", "Player", "Visuals", "World", "Misc" };

        for(auto name : names)
            new Category(this, name);
    };

    if(this->categories.empty())
        return;
    
    /* Combat */
    
    auto combat = this->getCategory("Combat");

    if(combat != nullptr) {
        /* Add Modules */
    };

    /* Movement */
    
    auto movement = this->getCategory("Movement");

    if(movement != nullptr) {
        new AirJump(movement);
    };

    /* Player */

    auto player = this->getCategory("Player");

    if(player != nullptr) {
        /* Add Modules */
    };

    /* Visuals */

    auto visuals = this->getCategory("Visuals");

    if(visuals != nullptr) {
        /* Add Modules */
    };

    /* World */

    auto world = this->getCategory("World");

    if(world != nullptr) {
        /* Add Modules */
    };

    /* Misc */

    auto misc = this->getCategory("Misc");

    if(misc != nullptr) {
        /* Add Modules */
    };

    for(;;) {
        for(auto c : this->categories)
            c->baseTick();
    };
};

auto Manager::getCategory(std::string name) -> Category* {
    for(auto c : this->categories)
        if(c->name.rfind(name) != std::string::npos)
            return c;
    return nullptr;
};

auto Manager::getCategory(size_t i) -> Category* {
    if(this->categories.empty() || (this->categories.size() - 1) < i)
        return nullptr;
    
    return this->categories.at(i);
};