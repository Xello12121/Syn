#ifndef CLIENT_SDK_CLASSES_GUIDATA
#define CLIENT_SDK_CLASSES_GUIDATA

class GuiData {
private:
    char pad_0x0000[0x38]; //0x0000
public:
	Vec3<float> res;       //0x0038 
private:
    char pad_0x0044[0x8];  //0x0044
public:
	float scale;           //0x004C
};

#endif /* CLIENT_SDK_CLASSES_GUIDATA */