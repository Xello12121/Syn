#include "Category.h"

#include "../Manager/Manager.h"
#include "../Module/Module.h"

Category::Category(Manager* manager, std::string name) {
    this->manager = manager;
    this->name = name;

    manager->categories.push_back(this);
};

auto Category::baseTick(void) -> void {
    for(auto m : this->modules)
        m->baseTick();
};

auto Category::getModule(std::string name) -> Module* {
    for(auto m : this->modules)
        if(m->name.rfind(name) != std::string::npos)
            return m;
    return nullptr;
};

auto Category::getModule(size_t i) -> Module* {
    if(this->modules.empty() || (this->modules.size() - 1) < i)
        return nullptr;
    
    return this->modules.at(i);
};