#include "Client.h"
#include "Syn/Manager/Manager.h"

Client::Client(std::string name) {
    this->name = name;
    this->manager = new Manager(this);
};