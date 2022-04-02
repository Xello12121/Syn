#ifndef CLIENT_SYN_MANAGER_MANAGER
#define CLIENT_SYN_MANAGER_MANAGER

#include "../../Utils/Utils.h"
#include "../../Mem/Mem.h"

class Client;
class Category;

class Manager {
public:
    Client* client = nullptr;
public:
    std::vector<Category*> categories;
public:
    Manager(Client*);
public:
    auto init(void) -> void;
public:
    auto getCategory(std::string) -> Category*;
    auto getCategory(size_t) -> Category*;
};

#endif /* CLIENT_SYN_MANAGER_MANAGER */