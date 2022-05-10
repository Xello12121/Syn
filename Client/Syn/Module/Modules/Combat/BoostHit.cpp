#include "BoostHit.h"
#include "../../../Category/Category.h"
#include "../../../Manager/Manager.h"

auto BoostHit::onAttack(GameMode* GM, Actor* entity) -> void {
    
    auto player = GM->player;
    
    auto myPos = *player->getPos();
    auto pos = *entity->getPos();

    auto dX = myPos.x - pos.x;
    auto dY = myPos.y - pos.y;
    auto dZ = myPos.z - pos.z;

    auto dist = sqrt(dX * dX + dY * dY + dZ * dZ);
    auto angles = Vec2<float>(-(float)atan2(dY, dist) * (180.f / 3.14), (float)atan2(dZ, dX) * (180.f / 3.14) + 90.f);
    
    auto tooClose = (dist <= 2.f);
    auto yaw = angles.y + (tooClose ? -90.f : 90.f);

    auto speed = this->boost;

    if(tooClose)
        speed += 2.f;

    player->velocity = (Vec3<float>(cos((yaw) * (3.14 / 180.0f)) * speed, player->velocity.y ,sin((yaw) * (3.14 / 180.0f)) * speed));

};