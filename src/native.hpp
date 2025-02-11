#ifndef NATIVE_HPP
#define NATIVE_HPP
#include <string>

typedef struct NativeInfo {
    int screenWidth;
    int screenHeight;
} NativeInfo;

typedef struct Keystroke {
    wchar_t Character;
} Keystroke;

bool NativeInit();
NativeInfo *NativeGetInfo();

bool NativeSendKeystrokes(const std::string &string);
bool NativeSendEscape();
bool NativeSendMouseClick(int x, int y, bool isRightClick);

#endif //NATIVE_HPP
