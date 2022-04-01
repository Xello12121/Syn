#ifndef CLIENT_SYN_CATEGORY_CATEGORY
#define CLIENT_SYN_CATEGORY_CATEGORY

#include "../../Utils/Utils.h"
#include "../../Mem/Mem.h"

class Manager;
class Module;

class Category {
public:
    Manager* manager = nullptr;
public:
    std::string name;
    std::vector<Module*> modules;
public:
    Category(Manager*, std::string);
public:
    auto getModule(std::string) -> Module*;
    auto getModule(size_t) -> Module*;
};

#endif /* CLIENT_SYN_CATEGORY_CATEGORY */