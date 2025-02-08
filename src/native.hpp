#ifndef NATIVE_HPP
#define NATIVE_HPP
#include <string>

typedef struct Keystroke {
    wchar_t Character;
} Keystroke;

bool NativeInit();

bool NativeSendKeystrokes(const std::string &string);
bool NativeSendMouseClick(bool isRightClick);

#endif //NATIVE_HPP
