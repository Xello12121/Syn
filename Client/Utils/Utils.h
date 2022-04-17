#ifndef UTILS_UTILS
#define UTILS_UTILS

#include <filesystem>
#include <Windows.h>
#include <algorithm>
#include <assert.h>
#include <fstream>
#include <vector>
#include <string>
#include <map>

#include <dxgi.h>
#include <d3d12.h>
#include <d2d1_1.h>
#include <dxgi1_4.h>
#include <dwrite_1.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dwrite.lib")

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

class Color {
public:
    float r, g, b, a;
public:
    Color(float r = 0, float g = 0, float b = 0, float a = 1) {
        this->r = (r / 255.f);
        this->g = (g / 255.f);
        this->b = (b / 255.f);
        this->a = (a * 255.f);
    };
};

class Renderer {
private:
    ID2D1RenderTarget* d2dRenderTarget = nullptr;

    ID2D1Factory* factory = nullptr;
    IDXGISurface* dxgiBackbuffer = nullptr;
    IDWriteFactory1* writeFactory = nullptr;

    IDWriteTextFormat* textFormat = nullptr;
    ID2D1SolidColorBrush* brush = nullptr;
private:
    bool initialized = false;
public:
    auto init(IDXGISwapChain*, ID3D12Device*) -> bool;
    auto releaseTextures() -> void;
    auto beginFrame() -> void;
    auto endFrame() -> void;
private:
    auto charToWStr(char const &c) -> std::wstring;
public:
    auto getTextWidth(std::wstring, float) -> float;
    auto getTextHeight(std::wstring, float) -> float;
public:
    auto drawString(std::wstring, float, Vec2<float>, Color) -> void;
    auto fillRectangle(Vec4<float>, Color color) -> void;
    auto drawRectangle(Vec4<float>, Color color, float) -> void;
};

#endif /* UTILS_UTILS */