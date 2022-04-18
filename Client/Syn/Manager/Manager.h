#ifndef CLIENT_SYN_MANAGER_MANAGER
#define CLIENT_SYN_MANAGER_MANAGER

#include "../../Utils/Utils.h"
#include "../../Mem/Mem.h"

class Client;
class Category;
class Actor;

class Manager {
public:
    Client* client = nullptr;
public:
    std::vector<Category*> categories;
public:
    std::map<uint64_t, Actor*> entityMap;
    std::map<uint64_t, bool> keyMap;
public:
    Vec2<int> mousePos;
public:
    Manager(Client*);
public:
    auto initHooks(void) -> void;
    auto init(void) -> void;
public:
    auto getCategory(std::string) -> Category*;
    auto getCategory(size_t) -> Category*;
};

#endif /* CLIENT_SYN_MANAGER_MANAGER */