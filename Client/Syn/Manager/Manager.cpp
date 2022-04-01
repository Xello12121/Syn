#include "Manager.h"

#include "../Category/Category.h"
#include "../Module/Module.h"

Manager::Manager(Client* client) {
    this->client = client;
    this->init();
};

auto Manager::init(void) -> void {
    if(this->categories.empty()) {
        auto names = { "Combat", "Movement", "Player", "Visuals", "World", "Misc" };

        for(auto name : names)
            this->categories.push_back(new Category(this, name));
    };

    if(this->categories.empty())
        return;
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