#define WIN32_LEAN_AND_MEAN
#include <codecvt>
#include <locale>
#include <windows.h>

#include "native.hpp"

static HWND hackmudWindow;

bool NativeInit() {
    hackmudWindow = FindWindow(nullptr, "hackmud");
    if (hackmudWindow == nullptr) return false;

    return true;
}

bool NativeSendKeystrokes(const std::string &string) {
    // Need to do some encoding juggling, cuz Windows is UTF-16
    const size_t bytesNeeded = MultiByteToWideChar(CP_UTF8, 0, string.c_str(), -1, nullptr, 0);
    const auto utf16 = new wchar_t[bytesNeeded];
    MultiByteToWideChar(CP_UTF8, 0, string.c_str(), -1, utf16, bytesNeeded);

    for (int i = 0; i < bytesNeeded && utf16[i] != 0; i++) {
        if (!PostMessage(hackmudWindow, WM_CHAR, utf16[i], 0)) {
            delete[] utf16;
            return false;
        }
    }

    delete[] utf16;
    return true;
}

bool NativeSendMouseClick(const bool isRightClick) {
    if (!PostMessage(hackmudWindow, isRightClick ? WM_RBUTTONDOWN : WM_LBUTTONDOWN, 0, MAKELONG(100, 100)))
        return false;

    return PostMessage(hackmudWindow, isRightClick ? WM_RBUTTONUP : WM_LBUTTONUP, 0, MAKELONG(100, 100));
}
