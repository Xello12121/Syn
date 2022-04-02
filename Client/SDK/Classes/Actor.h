#ifndef CLIENT_SDK_CLASSES_ACTOR
#define CLIENT_SDK_CLASSES_ACTOR

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
    virtual auto setScoreTag(std::string, std::allocator<char>) -> void;
};

#endif /* CLIENT_SDK_CLASSES_ACTOR */