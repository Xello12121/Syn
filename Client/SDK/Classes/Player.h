#ifndef CLIENT_SDK_CLASSES_PLAYER
#define CLIENT_SDK_CLASSES_PLAYER

#include "Actor.h"
#include "GameMode.h"

class Player : public Actor {
public:
    auto setFlightSpeed(float f) -> void {
        *(float*)((uintptr_t)(this) + 0x7C0) = f;
    };
public:
    virtual auto _removePassenger(uintptr_t*, bool, bool, bool) -> void;
    virtual auto _onSizeUpdated(void) -> void;
private:
    virtual auto Function275(void) -> void;
public:
    virtual auto knockback(Actor*, int, float, float, float, float, float) -> void;
private:
    virtual auto Function277(void) -> void;
public:
    virtual auto setSprinting(bool) -> void;
    virtual auto getHurtSound(void) -> int;
    virtual auto getDeathSound(void) -> int;
    virtual auto getItemInHandIcon(uintptr_t*, int) -> uintptr_t*;
    virtual auto getSpeed(void) -> float;
    virtual auto setSpeed(float) -> void;
    virtual auto getJumpPower(void) -> float;
    virtual auto hurtEffects(uintptr_t*, int, bool, bool) -> bool;
    virtual auto getMeleeWeaponDamageBonus(Actor*) -> __int64;
    virtual auto getMeleeKnockbackBonus(void) -> __int64;
    virtual auto travel(uintptr_t*, float, float, float) -> void;
    virtual auto travel(float, float, float) -> void;
    virtual auto applyFinalFriction(float, bool) -> void;
    virtual auto aiStep(uintptr_t*) -> void;
    virtual auto aiStep(void) -> void;
    virtual auto pushActors(void) -> void;
    virtual auto lookAt(Actor *, float, float) -> void;
    virtual auto isLookingAtAnEntity(void) -> bool;
    virtual auto checkSpawnRules(bool) -> bool;
    virtual auto checkSpawnObstruction(void) -> bool;
    virtual auto getAttackAnim(float) -> float;
    virtual auto getItemUseDuration(void) -> __int64;
    virtual auto getItemUseStartupProgress(void) -> float;
    virtual auto getItemUseIntervalProgress(void) -> float;
    virtual auto getItemUseIntervalAxis(void) -> __int64;
    virtual auto getTimeAlongSwing(void) -> __int64;
private:
    virtual auto Function304(void) -> void;
public:
    virtual auto getMaxHeadXRot(void) -> float;
private:
    virtual auto Function306(void) -> void;
public:
    virtual auto doHurtTarget(Actor*, int*) -> void;
private:
    virtual auto Function308(void) -> void;
public:
    virtual auto leaveCaravan(void) -> void;
    virtual auto joinCaravan(Actor*) -> void;
    virtual auto hasCaravanTail(void) -> bool;
    virtual auto getCaravanHead(void) -> __int64;
    virtual auto getArmorValue(void) -> __int64;
    virtual auto getArmorCoverPercentage(void) -> float;
    virtual auto getToughnessValue(void) -> __int64;
    virtual auto hurtArmorSlots(uintptr_t const &,int, std::bitset<4> const &) -> void;
    virtual auto setDamagedArmor(int, uintptr_t const &) -> void;
    virtual auto sendArmorDamage(std::bitset<4> const &) -> void;
    virtual auto sendArmor(std::bitset<4> const &) -> void;
    virtual auto containerChanged(int) -> void;
    virtual auto updateEquipment(void) -> void;
    virtual auto clearEquipment(void) -> __int64;
    virtual auto getAllArmorID(void) -> __int64;
    virtual auto getAllHand(void) -> __int64;
    virtual auto getAllEquipment(void) -> __int64;
    virtual auto getArmorTypeHash(void) -> __int64;
    virtual auto dropEquipmentOnDeath(void) -> void;
    virtual auto dropEquipmentOnDeath(uintptr_t*, int) -> void;
    virtual auto clearVanishEnchantedItemsOnDeath(void) -> void;
    virtual auto sendInventory(bool) -> void;
    virtual auto getDamageAfterEnchantReduction(uintptr_t*, float) -> float;
    virtual auto getDamageAfterArmorReduction(uintptr_t*, float) -> float;
    virtual auto getDamageAfterResistanceEffect(uintptr_t*, float) -> float;
    virtual auto createAIGoals(void) -> bool;
private:
    virtual auto Function335(void) -> void;
public:
    virtual auto setItemSlot(int, uintptr_t*) -> bool;
    virtual auto setTransitioningSitting(bool) -> void;
    virtual auto attackAnimation(Actor *, float) -> void;
private:
    virtual auto Function339(void) -> void;
    virtual auto Function340(void) -> void;
    virtual auto Function341(void) -> void;
    virtual auto Function342(void) -> void;
public:
    virtual auto ascendLadder(void) -> void;
    virtual auto ascendBlockByJumping(void) -> void;
    virtual auto descendBlockByCrouching(void) -> void;
    virtual auto dropContainer(void) -> void;
    virtual auto initBodyControl(void) -> __int64;
    virtual auto jumpFromGround(uintptr_t*) -> void;
    virtual auto jumpFromGround(void) -> void;
};

#endif /* CLIENT_SDK_CLASSES_PLAYER */