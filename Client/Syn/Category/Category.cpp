#include "Category.h"
#include "../Module/Module.h"

Category::Category(Manager* manager, std::string name) {
    this->manager = manager;
    this->name = name;
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