#ifndef CLIENT_SYN_MANAGER_MANAGER
#define CLIENT_SYN_MANAGER_MANAGER

#include "../../Utils/Utils.h"
#include "../../Mem/Mem.h"

class Client;
class Category;
class Player;
class Actor;

class Manager {
public:
    Client* client = nullptr;
public:
    std::vector<Category*> categories;
public:
    std::map<uint64_t, Actor*> entityMap;
    std::map<uint64_t, bool> keyMap;
    std::map<char, std::pair<Vec2<int>, bool>> mouseData;
public:
    Manager(Client*);
public:
    auto initHooks(void) -> void;
    auto init(void) -> void;
public:
    auto getCategory(std::string) -> Category*;
    auto getCategory(size_t) -> Category*;
public:
    auto isUsingKey(uint64_t) -> bool;
};

#endif /* CLIENT_SYN_MANAGER_MANAGER */