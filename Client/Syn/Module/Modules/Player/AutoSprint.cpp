#include "AutoSprint.h"

auto AutoSprint::onGameMode(GameMode* GM) -> void {
    auto player = GM->player;

    if(player != nullptr)
        player->setSprinting(true);
};