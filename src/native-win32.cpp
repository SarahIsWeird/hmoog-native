#define WIN32_LEAN_AND_MEAN
#include <cassert>
#include <codecvt>
#include <cstdint>
#include <windows.h>

#include "native.hpp"

static HWND hackmudWindow = nullptr;
static NativeInfo nativeInfo;

typedef union WinKeystroke {
    struct {
        uint16_t repeatCount;
        uint8_t scanCode;
        uint8_t extended : 1;
        uint8_t reserved : 4;
        uint8_t contextCode : 1;
        uint8_t previousState : 1;
        uint8_t transitionState : 1;
    };
    LPARAM lParam;
} WinKeystroke;

static bool moveMouse(const long x, const long y) {
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dx = x * 65535 / nativeInfo.screenWidth;
    input.mi.dy = y * 65535 / nativeInfo.screenHeight;
    input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    input.mi.time = 0;
    input.mi.mouseData = 0;

    return SendInput(1, &input, sizeof(INPUT)) == 1;
}

static bool setMouseState(const bool isRight, const bool isDown) {
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dx = 0;
    input.mi.dy = 0;
    input.mi.time = 0;
    input.mi.dwExtraInfo = 0;
    input.mi.mouseData = 0;
    if (isRight) {
        input.mi.dwFlags = isDown ? MOUSEEVENTF_RIGHTDOWN : MOUSEEVENTF_RIGHTUP;
    } else {
        input.mi.dwFlags = isDown ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_LEFTUP;
    }

    return SendInput(1, &input, sizeof(INPUT)) == 1;
}

static bool setFakeFocus(const bool isFocused) {
    // Thank you michael for telling me how to fake focus Hackmud!
    return PostMessage(hackmudWindow, WM_ACTIVATE, isFocused ? WA_CLICKACTIVE : WA_INACTIVE, 0);
}

bool NativeInit() {
    hackmudWindow = FindWindow(nullptr, "hackmud");
    if (hackmudWindow == nullptr) return false;

    nativeInfo.screenWidth = GetSystemMetrics(SM_CXSCREEN);
    nativeInfo.screenHeight = GetSystemMetrics(SM_CYSCREEN);

    return true;
}

NativeInfo *NativeGetInfo() {
    if (hackmudWindow == nullptr) return nullptr;
    return &nativeInfo;
}

bool NativeSendKeystrokes(const std::string &string) {
    // Need to do some encoding juggling, cuz Windows is UTF-16
    const int bytesNeeded = MultiByteToWideChar(CP_UTF8, 0, string.c_str(), -1, nullptr, 0);
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

bool NativeSendEscape() {
    // Technically not needed, but better be safe than sorry.
    constexpr WinKeystroke keystrokeDown = {
        .scanCode = 0x1,
    };

    // Definitely needed, because of the previous state and the transition state.
    // If we don't pass this, the inputs seem to be repeated for a while, and very inconsistently at that.
    constexpr WinKeystroke keystrokeUp = {
        .scanCode = 0x1,
        .previousState = 1,
        .transitionState = 1,
    };

    if (!setFakeFocus(true)) return false;
    if (!PostMessage(hackmudWindow, WM_KEYDOWN, VK_ESCAPE, 0)) return false;
    if (!PostMessage(hackmudWindow, WM_KEYUP, VK_ESCAPE, keystrokeUp.lParam)) return false;
    Sleep(100); // Let Hackmud catch up
    if (!setFakeFocus(false)) return false;

    return true;
}

bool NativeSendMouseClick(const int x, const int y, const bool isRightClick) {
    // Windows only allows us to do mouse stuff if the window is in the foreground. :(
    if (!ShowWindow(hackmudWindow, SW_NORMAL)) return false;
    Sleep(50);

    moveMouse(x, y);
    Sleep(50);

    setMouseState(isRightClick, true);
    Sleep(50);
    setMouseState(isRightClick, false);

    if (!ShowWindow(hackmudWindow, SW_MINIMIZE)) return false;

    return true;
}
