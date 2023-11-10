/**
    Belu Antonie-Gabriel
    Last updated: 10/11/2023
    belutoni06@gmail.com
**/

#pragma once
// Bare-bones of the app
#include "basewin.h"
#define WM_CHAR                         0x0102

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

#ifdef DEBUG_BTAG_CODE
#define LOG(where, what, severity, id) { \
    std::ofstream LOGMSG;                \
    LOGMSG.open("runtime.log", std::ios::app); \
    std::time_t now = std::time(nullptr);                                     \
    LOGMSG << std::left << "<" << (id) << " : " << std::string(std::ctime(&now)).substr(11, 8) << "> " \
           << "[" << (severity) << "] " \
           << std::setw(128) << (where) << ": " << std::setw(64) << (what) << '\n'; \
    LOGMSG.close(); \
    }
#define APP_RETURN_MACRO(CODE, TYPE, ID) { \
LOG("GLOBAL", #CODE, (TYPE), (ID))                                 \
return CODE;              \
} void()
#define FAST_LOG(msg) LOG("FastLog message", (msg), "Fast", 0)
#else
#define APP_RETURN_MACRO(CODE) return CODE;
#endif

template <class T> void SafeRelease(T **ppT) {
    if (*ppT != nullptr) {
        (*ppT)->Release();
        *ppT = nullptr;
    }
}

// 0 is used for global messages
static unsigned long long WIN_ID = 1;
namespace MWND {
    class MainWindow : public BWND::BaseWin<MainWindow> {
        const wchar_t *CLASSNAME;
        ID2D1Factory *pFactory;
        ID2D1HwndRenderTarget *pRenderTarget;
        ID2D1SolidColorBrush *pBrush;
        IDWriteFactory *pDWriteFactory;
        D2D1_RECT_U fRect{};
        std::wstring fContent = L"The GetAsyncKeyState function works with mouse buttons. However, it checks on the state of the physical mouse buttons, not on the logical mouse buttons that the physical buttons are mapped to. For example, the call GetAsyncKeyState(VK_LBUTTON) always returns the state of the left physical mouse button, regardless of whether it is mapped to the left or right logical mouse button. You can determine the system's current mapping of physical mouse buttons to logical mouse buttons by calling GetSystemMetrics(SM_SWAPBUTTON).\n"
                                "\n"
                                "which returns TRUE if the mouse buttons have been swapped.\n"
                                "\n"
                                "Although the least significant bit of the return value indicates whether the key has been pressed since the last query, due to the preemptive multitasking nature of Windows, another application can call GetAsyncKeyState and receive the \"recently pressed\" bit instead of your application. The behavior of the least significant bit of the return value is retained strictly for compatibility with 16-bit Windows applications (which are non-preemptive) and should not be relied upon.\n"
                                "\n"
                                "You can use the virtual-key code constants VK_SHIFT, VK_CONTROL, and VK_MENU as values for the vKey parameter. This gives the state of the SHIFT, CTRL, or ALT keys without distinguishing between left and right.\n"
                                "\n"
                                "You can use the following virtual-key code constants as values for vKey to distinguish between the left and right instances of those keys.";

        HRESULT CreateGraphicsResources();
        void DiscardGraphicsResources();
        void OnPaint();
        void Resize();
    public:
        unsigned short ID;
        [[nodiscard]] PCWSTR ClassName() const override { return CLASSNAME; }
        LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
        void MessageLoop(UINT wMsgFilterMin, UINT wMsgFilterMax) override;

        // Ctor
        explicit MainWindow(const wchar_t *className) : pFactory(nullptr), pRenderTarget(nullptr), pBrush(nullptr), pDWriteFactory(nullptr), ID(WIN_ID++) {
            LOG("MainWindow()", "Created new window", "Info", ID)
            CLASSNAME = className;
        }
        // Dctor
        ~MainWindow() {
            LOG("~MainWindow()", "Destroying window and all related resources", "Info", ID)
            DiscardGraphicsResources();
            SafeRelease(&pFactory);
            SafeRelease(&pDWriteFactory);
        }
    };
}