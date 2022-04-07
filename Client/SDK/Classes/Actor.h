#ifndef CLIENT_SDK_CLASSES_ACTOR
#define CLIENT_SDK_CLASSES_ACTOR

#include "Level.h"

class Actor {
private:
    char pad_0008[304];    //0x0008
public:
	Vec2<float> bodyRot;   //0x0138
private:
	char pad_0140[152];    //0x0140
public:
	bool onGround;         //0x01D8
private:
	char pad_01D9[767];    //0x01D9
public:
	Vec3<float> pos;       //0x04D8
private:
	char pad_04E4[12];     //0x04E4
public:
	Vec3<float> velocity;  //0x04F0
private:
	char pad_04FC[84];     //0x04FC
public:
	uint64_t runtimeId;    //0x0550
public:
    auto getLevel(void) -> Level* {
        return *(Level**)((uintptr_t)(this) + 0x368);
    };
private:
    virtual auto Function0(void) -> void;
    virtual auto Function1(void) -> void;
    virtual auto Function2(void) -> void;
    virtual auto Function3(void) -> void;
    virtual auto Function4(void) -> void;
    virtual auto Function5(void) -> void;
    virtual auto Function6(void) -> void;
public:
    virtual auto outOfWorld(void) -> bool;
private:
    virtual auto Function8(void) -> void;
    virtual auto Function9(void) -> void;
    virtual auto Function10(void) -> void;
    virtual auto Function11(void) -> void;
    virtual auto Function12(void) -> void;
    virtual auto Function13(void) -> void;
    virtual auto Function14(void) -> void;
public:
    virtual auto reset(void) -> void;
    virtual auto getOnDeathExperience(void) -> __int64;
    virtual auto getOwnerEntityType(void) -> int;
    virtual auto remove(void) -> void;
    virtual auto setPos(Vec3<float>*) -> void;
private:
    virtual auto Function20(void) -> void;
    virtual auto Function21(void) -> void;
public:
    virtual auto getPos(void) -> Vec3<float>*;
    virtual auto getPosOld(void) -> Vec3<float>*;
    virtual auto getPosExtrapolated(float) -> Vec3<float>;
    virtual auto getAttachPos(int, float) -> Vec3<float>;
    virtual auto getFiringPos(void) -> Vec3<float>;
    virtual auto setRot(Vec2<float>*) -> void;
    virtual auto move(uintptr_t*, Vec3<float>*) -> void;
    virtual auto move(Vec3<float>*) -> void;
    virtual auto getInterpolatedRidingPosition(float) -> Vec3<float>;
    virtual auto getInterpolatedBodyRot(float) -> float;
private:
    virtual auto Function32(void) -> void;
    virtual auto Function33(void) -> void;
public:
    virtual auto getYawSpeedInDegreesPerSecond(void) -> float;
    virtual auto getInterpolatedWalkAnimSpeed(float) -> float;
    virtual auto getWorldPosition(void) -> Vec3<float>;
private:
    virtual auto Function37(void) -> void;
public:
    virtual auto updateEntityInside(void) -> void;
    virtual auto updateEntityInside(AABB<float>*) -> void;
    virtual auto isFireImmune(void) -> bool;
private:
    virtual auto Function41(void) -> void;
public:
    virtual auto blockedByShield(uintptr_t*, Actor*) -> void;
    virtual auto teleportTo(Vec3<float>*, bool, int, int) -> void;
    virtual auto tryTeleportTo(Vec3<float>*, bool, bool, int, int) -> void;
    virtual auto chorusFruitTeleport(Vec3<float>*) -> void;
    virtual auto lerpMotion(Vec3<float>*) -> void;
    virtual auto tryCreateAddActorPacket(void) -> __int64;
    virtual auto normalTick(void) -> void;
    virtual auto baseTick(void) -> void;
    virtual auto vehicleTick(void) -> void;
    virtual auto positionPassenger(Actor*, float) -> void;
    virtual auto getRidingHeight(void) -> float;
    virtual auto startRiding(Actor*) -> bool;
    virtual auto addPassenger(Actor*) -> void;
    virtual auto flagPassengerToRemove(Actor*) -> void;
private:
    virtual auto Function56(void) -> void;
public:
    virtual auto intersects(Vec3<float>*, Vec3<float>*) -> bool;
    virtual auto isInWall(void) -> bool;
    virtual auto isInvisible(void) -> bool;
    virtual auto canShowNameTag(void) -> bool;
private:
    virtual auto Function61(void) -> void;
public:
    virtual auto setNameTagVisible(bool) -> void;
    virtual auto getNameTag(void) -> std::string;
    virtual auto getNameTagAsHash(void) -> unsigned __int64;
    virtual auto getFormattedNameTag(void) -> std::string;
    virtual auto filterFormattedNameTag(uintptr_t*) -> void;
    virtual auto setNameTag(std::string) -> void;
private:
    virtual auto Function68(void) -> void;
public:
    virtual auto setScoreTag(std::string) -> void;
    virtual auto getScoreTag(void) -> std::string;
    virtual auto isInWater(void) -> bool;
    virtual auto hasEnteredWater(void) -> bool;
    virtual auto isInLava(void) -> bool;
    virtual auto isUnderLiquid(int) -> bool;
    virtual auto isOverWater(void) -> bool;
    virtual auto setBlockMovementSlowdownMultiplier(Vec3<float>*) -> void;
    virtual auto resetBlockMovementSlowdownMultiplier(void) -> void;
    virtual auto getCameraOffset(void) -> float;
    virtual auto getShadowHeightOffs(void) -> float;
    virtual auto getShadowRadius(void) -> float;
    virtual auto getHeadLookVector(float) -> Vec3<float>;
private:
    virtual auto Function82(void) -> void;
public:
    virtual auto canSee(Vec3<float>*) -> bool;
    virtual auto canSee(Actor*) -> bool;
    virtual auto isSkyLit(float) -> bool;
    virtual auto getBrightness(float) -> float;
private:
    virtual auto Function87(void) -> void;
    virtual auto Function88(void) -> void;
public:
    virtual auto onAboveBubbleColumn(bool) -> void;
    virtual auto onInsideBubbleColumn(bool) -> void;
    virtual auto isImmobile(void) -> bool;
    virtual auto isSilent(void) -> bool;
    virtual auto isPickable(void) -> bool;
private:
    virtual auto Function94(void) -> void;
public:
    virtual auto isSleeping(void) -> bool;
    virtual auto setSleeping(bool) -> void;
private:
    virtual auto Function97(void) -> void;
public:
    virtual auto setSneaking(bool) -> void;
    virtual auto isBlocking(void) -> bool;
    virtual auto isDamageBlocked(uintptr_t*) -> bool;
    virtual auto isAlive(void) -> bool;
    virtual auto isOnFire(void) -> bool;
    virtual auto isOnHotBlock(void) -> bool;
private:
    virtual auto Function104(void) -> void;
public:
    virtual auto isSurfaceMob(void) -> bool;
private:
    virtual auto Function106(void) -> void;
    virtual auto Function107(void) -> void;
    virtual auto Function108(void) -> void;
public:
    virtual auto isAffectedByWaterBottle(void) -> bool;
    virtual auto canAttack(Actor*, bool) -> bool;
    virtual auto setTarget(Actor*) -> void;
private:
    virtual auto Function112(void) -> void;
public:
    virtual auto isValidTarget(Actor*) -> bool;
    virtual auto attack(Actor*, int*) -> bool;
    virtual auto performRangedAttack(Actor*, float) -> void;
    virtual auto adjustDamageAmount(int*) -> void;
    virtual auto getEquipmentCount(void) -> __int64;
    virtual auto setOwner(__int64) -> void;
    virtual auto setSitting(bool) -> void;
private:
    virtual auto Function120(void) -> void;
    virtual auto Function121(void) -> void;
public:
    virtual auto getInventorySize(void) -> __int64;
    virtual auto getEquipSlots(void) -> __int64;
    virtual auto getChestSlots(void) -> __int64;
    virtual auto setStanding(bool) -> void;
    virtual auto canPowerJump(void) -> bool;
    virtual auto setCanPowerJump(bool) -> void;
    virtual auto isJumping(void) -> bool;
    virtual auto isEnchanted(void) -> bool;
private:
    virtual auto Function130(void) -> void;
public:
    virtual auto shouldRender(void) -> bool;
    virtual auto playAmbientSound(void) -> void;
    virtual auto getAmbientSound(void) -> int;
    virtual auto isInvulnerableTo(uintptr_t*) -> bool;
    virtual auto getBlockDamageCause(uintptr_t const &) -> int;
    virtual auto actuallyHurt(int, uintptr_t*, bool) -> void;
    virtual auto animateHurt(void) -> void;
    virtual auto doFireHurt(int) -> bool;
    virtual auto onLightningHit(void) -> void;
    virtual auto onBounceStarted(Vec3<int>*, uintptr_t*) -> void;
    virtual auto feed(int) -> void;
    virtual auto handleEntityEvent(int, int) -> void;
    virtual auto getPickRadius(void) -> float;
    virtual auto getActorRendererId(void) -> __int64;
    virtual auto spawnAtLocation(uintptr_t*, float) -> uintptr_t*;
    virtual auto spawnAtLocation(uintptr_t*, int, float) -> uintptr_t*;
    virtual auto spawnAtLocation(uintptr_t*, int) -> uintptr_t*;
    virtual auto spawnAtLocation(int, int, float) -> uintptr_t*;
    virtual auto spawnAtLocation(int, int) -> uintptr_t*;
    virtual auto despawn(void) -> void;
    virtual auto killed(Actor*) -> void;
    virtual auto awardKillScore(Actor*, int) -> void;
    virtual auto setArmor(int, uintptr_t*) -> void;
    virtual auto getArmor(int) -> uintptr_t;
    virtual auto getAllArmor(void) -> std::vector<uintptr_t*>;
    virtual auto getArmorMaterialTypeInSlot(int) -> int;
    virtual auto getArmorMaterialTextureTypeInSlot(int) -> int;
    virtual auto getArmorColorInSlot(int, int) -> float;
    virtual auto getEquippedSlot(int) -> uintptr_t*;
    virtual auto setEquippedSlot(int, uintptr_t*) -> void;
    virtual auto getSelectedItem(void) -> uintptr_t*;
    virtual auto setCarriedItem(uintptr_t*) -> void;
    virtual auto setOffhandSlot(uintptr_t*) -> void;
    virtual auto getEquippedTotem(void) -> uintptr_t*;
    virtual auto consumeTotem(void) -> void;
private:
    virtual auto Function166(void) -> void;
    virtual auto Function167(void) -> void;
    virtual auto Function168(void) -> void;
    virtual auto Function169(void) -> void;
public:
    virtual auto getEntityTypeId(void) -> uint8_t;
private:
    virtual auto Function171(void) -> void;
public:
    virtual auto getSourceUniqueID(void) -> __int64;
    virtual auto thawFreezeEffect(void) -> void;
    virtual auto canFreeze(void) -> bool;
    virtual auto isWearingLeatherArmor(void) -> bool;
    virtual auto getLiquidAABB(int) -> AABB<float>;
    virtual auto handleInsidePortal(Vec3<int>*) -> void;
private:
    virtual auto Function178(void) -> void;
public:
    virtual auto getPortalWaitTime(void) -> __int64;
    virtual auto getDimensionId(void) -> __int64;
    virtual auto canChangeDimensions(void) -> bool;
private:
    virtual auto Function182(void) -> void;
public:
    virtual auto changeDimension(__int64, int) -> __int64;
    virtual auto getControllingPlayer(void) -> __int64;
    virtual auto checkFallDamage(float, bool) -> void;
    virtual auto causeFallDamage(float, float, __int64) -> void;
    virtual auto handleFallDistanceOnServer(float, float, bool) -> void;
    virtual auto playSynchronizedSound(int, Vec3<float>, int, bool) -> void;
    virtual auto playSynchronizedSound(int, Vec3<float>, __int64, bool) -> void;
private:
    virtual auto Function190(void) -> void;
    virtual auto Function191(void) -> void;
public:
    virtual auto canAddPassenger(Actor*) -> bool;
private:
    virtual auto Function193(void) -> void;
    virtual auto Function194(void) -> void;
public:
    virtual auto inCaravan(void) -> bool;
private:
    virtual auto Function196(void) -> void;
public:
    virtual auto tickLeash(void) -> void;
private:
    virtual auto Function198(void) -> void;
    virtual auto Function199(void) -> void;
public:
    virtual auto stopRiding(bool, bool, bool) -> void;
    virtual auto startSwimming(void) -> void;
    virtual auto stopSwimming(void) -> void;
private:
    virtual auto Function203(void) -> void;
public:
    virtual auto getCommandPermissionLevel(void) -> int;
    virtual auto isClientSide(void) -> bool;
    virtual auto getMutableAttribute(uintptr_t*) -> uintptr_t*;
    virtual auto getAttribute(uintptr_t*) -> uintptr_t*;
    virtual auto getDeathTime(void) -> __int64;
    virtual auto heal(int) -> void;
    virtual auto isInvertedHealAndHarm(void) -> bool;
    virtual auto canBeAffected(uintptr_t*) -> bool;
    virtual auto canBeAffected(int) -> bool;
    virtual auto canBeAffectedByArrow(uintptr_t*) -> bool;
private:
    virtual auto Function214(void) -> void;
    virtual auto Function215(void) -> void;
    virtual auto Function216(void) -> void;
public:
    virtual auto getAnimationComponent(void) -> uintptr_t*;
    virtual auto openContainerComponent(Actor*) -> void;
    virtual auto swing(void) -> void;
};

#endif /* CLIENT_SDK_CLASSES_ACTOR */