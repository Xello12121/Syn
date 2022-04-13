#ifndef CLIENT_SDK_CLASSES_GUIDATA
#define CLIENT_SDK_CLASSES_GUIDATA

class GuiData {
private:
    char pad_0000[24];     //0x0000
public:
    Vec2<float> res;       //0x0018
private:
    char pad_0020[8];      //0x0020
public:
    Vec2<float> scaledRes; //0x0028
private:
    char pad_0030[8];      //0x0030
private:
    float scale;           //0x0038
private:
    char pad_003C[22];     //0x003C
public:
    Vec2<short> mousePos;  //0x0052
};

#endif /* CLIENT_SDK_CLASSES_GUIDATA */