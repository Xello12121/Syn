#include "Module.h"

Module::Module(Category* category, std::string name) {
    this->category = category;
    this->name = name;
};

auto Module::baseTick(void) -> void {
    if(this->isEnabled != this->wasEnabled) {
        this->wasEnabled = this->isEnabled;

        if(this->isEnabled)
            this->onEnable();
        else
            this->onDisable();
    };

    if(this->isEnabled)
        this->onTick();
};