/**
    Belu Antonie-Gabriel
    Last updated: 11/8/2023
    Do not publish this code; if you somehow
    get a copy of it, remove it and report it at
    belutoni06@gmail.com
**/

#pragma once
// Bare-bones of the app
#include "basewin.h"

// C++ Header Files
#include <algorithm>
#include <string>
#include <thread>
#include <fstream>
#include <iomanip>
#include <ctime>

// Direct2D
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

// C Header Files
#include <cstdlib>
#include <malloc.h>
#include <memory.h>
#include <cwchar>
#include <cmath>

#ifdef _LAEXPLORER_DEBUG_MODE
#define APP_RETURN_MACRO(CODE) { \
std::string _LAEXPLORER_DEBUG_MODE_STRING_VARIABLE_NAME = #CODE;                          \
std::wstring _LAEXPLORER_DEBUG_MODE_WSTRING_VARIABLE_NAME(_LAEXPLORER_DEBUG_MODE_STRING_VARIABLE_NAME.begin(), _LAEXPLORER_DEBUG_MODE_STRING_VARIABLE_NAME.end() ); \
const wchar_t* _LAEXPLORER_DEBUG_MODE_WCHAR_VARIABLE_NAME = _LAEXPLORER_DEBUG_MODE_WSTRING_VARIABLE_NAME.c_str(); \
MessageBoxExW(nullptr, _LAEXPLORER_DEBUG_MODE_WCHAR_VARIABLE_NAME, L"DEBUG MODE", MB_OK, 0);                                         \
return CODE;              \
} void()
#define LOG(where, what, severity, id) { \
    std::ofstream LOGMSG;                \
    LOGMSG.open("runtime.log", std::ios::app); \
    std::time_t now = std::time(nullptr);                                     \
    LOGMSG << std::left << "<" << (id) << " : " << std::string(std::ctime(&now)).substr(11, 8) << "> " \
           << "[" << (severity) << "] " \
           << std::setw(64) << (where) << ": " << std::setw(32) << (what) << '\n'; \
    LOGMSG.close(); \
    }
#else
#define APP_RETURN_MACRO(CODE) return CODE;
#endif

template <class T> void SafeRelease(T **ppT) {
    if (*ppT) {
        (*ppT)->Release();
        *ppT = nullptr;
    }
}


static unsigned long long WIN_ID = 0;
namespace MWND {
    class MainWindow : public BWND::BaseWin<MainWindow> {
        const wchar_t *WINDOWNAME;
        unsigned long long ID;
        ID2D1Factory *pFactory;
        ID2D1HwndRenderTarget *pRenderTarget;
        ID2D1SolidColorBrush *pBrush;
        IDWriteFactory *pDWriteFactory;
        D2D1_RECT_U fRect;

        HRESULT CreateGraphicsResources();
        void DiscardGraphicsResources();
        void OnPaint();
        void Resize();
    public:
        [[nodiscard]] PCWSTR ClassName() const override { return WINDOWNAME; }
        LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
        void MessageLoop(UINT wMsgFilterMin, UINT wMsgFilterMax) override;
        MainWindow(const wchar_t *className) : pFactory(nullptr), pRenderTarget(nullptr), pBrush(nullptr), pDWriteFactory(nullptr), ID(WIN_ID++) {
            LOG("MainWindow()", "Created new window", "Info", ID);
            WINDOWNAME = className;
        }
    };
}