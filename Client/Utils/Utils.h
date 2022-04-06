#ifndef UTILS_UTILS
#define UTILS_UTILS

#include <filesystem>
#include <Windows.h>
#include <assert.h>
#include <fstream>
#include <vector>
#include <string>
#include <map>

class Utils {
public:
    static auto GetDll(void) -> HMODULE;
public:
    static auto getDebugDir(void) -> std::string;
public:
    static auto debugLog(std::string) -> void;
};

template<typename T>
class Vec2 {
public:
    T x;
    T y;
public:
    Vec2(T x = 0, T y = 0) {
        this->x = x;
        this->y = y;
    };
};

template<typename T>
class Vec3 : public Vec2<T> {
public:
    T z;
public:
    Vec3(T x = 0, T y = 0, T z = 0) {
        this->x = x;
        this->y = y;
        this->z = z;
    };
};

template<typename T>
class Vec4 : public Vec3<T> {
public:
    T w;
public:
    Vec4(T x = 0, T y = 0, T z = 0, T w = 0) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    };
};

template<typename T>
class AABB {
public:
    T a;
    T b;
public:
    AABB(Vec3<T> vA, Vec3<T> vB) {
        this->a = vA;
        this->b = vB;
    };
};

#endif /* UTILS_UTILS */