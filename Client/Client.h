#ifndef CLIENT_CLIENT
#define CLIENT_CLIENT

#include "Utils/Utils.h"
#include "Mem/Mem.h"

class Manager;

class Client {
public:
    Manager* manager = nullptr;
public:
    std::string name;
public:
    Client(std::string);
};

#endif /* CLIENT_CLIENT */