#include "Utils.h"

auto Utils::GetDll(void) -> HMODULE {
    MEMORY_BASIC_INFORMATION info;
    size_t len = VirtualQueryEx(GetCurrentProcess(), (void*)GetDll, &info, sizeof(info));
    assert(len == sizeof(info));
    return len ? (HMODULE)info.AllocationBase : NULL;
};

auto Utils::getDebugDir(void) -> std::string {
    char* path = NULL;
    size_t length;

    _dupenv_s(&path, &length, "appdata");

    return std::string(path);
};

auto Utils::debugLog(std::string output) -> void {
    static bool init = false;
    static auto path = std::string(getDebugDir() + "\\..\\Local\\Packages\\Microsoft.MinecraftUWP_8wekyb3d8bbwe\\RoamingState");

    auto file = std::string(path + "\\Output.txt");
    
    if(!init) {
        auto f = std::filesystem::path(file);

        if(std::filesystem::exists(f))
            std::filesystem::remove(f);
        
        init = true;
    };
    
    CloseHandle(CreateFileA(file.c_str(), GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL));

    std::ofstream fStream;
    fStream.open(file.c_str(), std::ios::app);
    
    if(fStream.is_open())
        fStream << output << "\n" << std::endl;
    
    return fStream.close();
};


auto Renderer::init(IDXGISwapChain* pChain, ID3D12Device* pDevice) -> void {

    D2D1_FACTORY_OPTIONS options;
    options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, options, &factory);

    pChain->GetBuffer(0, IID_PPV_ARGS(&dxgiBackbuffer));

    D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties( D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));
    factory->CreateDxgiSurfaceRenderTarget(dxgiBackbuffer, props, &d2dRenderTarget);
    dxgiBackbuffer->Release();

    DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(writeFactory), (IUnknown**)(&writeFactory));
};

auto Renderer::releaseTextures() -> void {
    if(this->d2dRenderTarget != nullptr)
        this->d2dRenderTarget->Release();
    
    if(this->writeFactory != nullptr)
        this->writeFactory->Release();
    
    if(this->factory != nullptr)
        this->factory->Release();
};

auto Renderer::beginFrame() -> void {
    d2dRenderTarget->BeginDraw();
};

auto Renderer::endFrame() -> void {
    d2dRenderTarget->EndDraw();
};

auto Renderer::charToWStr(char const &c) -> std::wstring {
    std::ostringstream o;
    o << c;

    auto str = o.str();
    return std::wstring(str.begin(), str.end());
};

auto Renderer::getTextWidth(std::wstring text, float size) -> float {
    auto len = 0.f;
    
    std::for_each(text.begin(), text.end(), [&](char const &c) {
        auto wstr = this->charToWStr(c);

        if(wstr == L" ")
            len += (size / 2.5);

        IDWriteTextLayout* layout = nullptr;
        writeFactory->CreateTextFormat(L"Arial", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, size, L"", &textFormat);
        writeFactory->CreateTextLayout(wstr.c_str(), wcslen(wstr.c_str()), textFormat, 0.0f, 0.0f, &layout);

        DWRITE_TEXT_METRICS metrics;
        layout->GetMetrics(&metrics);

        len += metrics.width;

        if(textFormat != nullptr)
            textFormat->Release();
        
        if(layout != nullptr)
            layout->Release();
    });
    
    return len;
};

auto Renderer::getTextHeight(std::wstring text, float size) -> float {
    auto height = 0.f;

    std::for_each(text.begin(), text.end(), [&](char const &c) {
        auto wstr = this->charToWStr(c);

        IDWriteTextLayout* layout = nullptr;
        writeFactory->CreateTextFormat(L"Arial", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, size, L"", &textFormat);
        writeFactory->CreateTextLayout(wstr.c_str(), wcslen(wstr.c_str()), textFormat, 0.0f, 0.0f, &layout);

        DWRITE_TEXT_METRICS metrics;
        layout->GetMetrics(&metrics);

        auto curr = metrics.height;
        if(curr > height)
            height = curr;

        if(textFormat != nullptr)
            textFormat->Release();
        
        if(layout != nullptr)
            layout->Release();
    });
    
    return height;
};

auto Renderer::drawString(std::wstring text, float size, Vec2<float> pos, Color color) -> void {
    writeFactory->CreateTextFormat(L"Arial", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, size, L"", &textFormat);
    d2dRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color.r, color.g, color.b, 1.f), &brush);
    d2dRenderTarget->DrawText(text.c_str(), wcslen(text.c_str()), textFormat, D2D1::RectF(pos.x, pos.y, pos.x + 1000, pos.y + 1000), brush);

    if(textFormat != nullptr)
        textFormat->Release();
    
    if(brush != nullptr)
        brush->Release();
};

auto Renderer::fillRectangle(Vec4<float> rectPos, Color color) -> void {
    d2dRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color.r, color.g, color.b, color.a), &brush);
    d2dRenderTarget->FillRectangle(D2D1::RectF(rectPos.x, rectPos.y, rectPos.z, rectPos.w), brush);

    if(brush != nullptr)
        brush->Release();
};

auto Renderer::drawRectangle(Vec4<float> rectPos, Color color, float lineWidth) -> void {
    d2dRenderTarget->CreateSolidColorBrush(D2D1::ColorF(color.r, color.g, color.b, color.a), &brush);
    d2dRenderTarget->DrawRectangle(D2D1::RectF(rectPos.x, rectPos.y, rectPos.z, rectPos.w), brush, lineWidth);

    if(brush != nullptr)
        brush->Release();
};