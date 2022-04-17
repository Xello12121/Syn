#include "Client.h"
#include "Syn/Manager/Manager.h"

Client::Client(std::string name) {
    Utils::debugLog("Initiating Client Instance with name: " + name);
    
    this->name = name;
    this->manager = new Manager(this);
};