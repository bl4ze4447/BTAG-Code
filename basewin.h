/**
    Belu Antonie-Gabriel
    Last updated: 10/11/2023
    belutoni06@gmail.com
**/

#pragma once

#ifndef UNICODE // fuck this
#define UNICODE
#endif

#define DEBUG_BTAG_CODE

#include <windows.h>
#include "appcodes.h"

// We luv microsoft <3
namespace BWND {
    template <typename DERIVED_TYPE>
    class BaseWin {
    public:
        HWND m_hwnd;
        BaseWin() : m_hwnd(nullptr) {}
        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
            DERIVED_TYPE *pThis;

            if (uMsg == WM_NCCREATE) {
                auto pCreate = reinterpret_cast<CREATESTRUCTW *>(lParam);
                pThis = static_cast<DERIVED_TYPE*>(pCreate->lpCreateParams);
                SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
                pThis->m_hwnd = hwnd;
            } else {
                pThis = reinterpret_cast<DERIVED_TYPE*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
            }

            if (pThis) {
                return pThis->HandleMessage(uMsg, wParam, lParam);
            } else {
                return DefWindowProc(hwnd, uMsg, wParam, lParam);
            }
        }
        BOOL Create(
                PCWSTR lpWindowName,
                DWORD dwStyle,
                DWORD dwExStyle = 0,
                int x = CW_USEDEFAULT,
                int y = CW_USEDEFAULT,
                int nWidth = CW_USEDEFAULT,
                int nHeight = CW_USEDEFAULT,
                HWND hwndParent = nullptr,
                HMENU hMenu = nullptr
        ) {
            WNDCLASS wndClass{0};

            wndClass.style = CS_DBLCLKS;
            wndClass.lpfnWndProc = DERIVED_TYPE::WindowProc;
            wndClass.hInstance = GetModuleHandle(nullptr);
            wndClass.lpszClassName = ClassName();
            RegisterClassW(&wndClass);

            m_hwnd = CreateWindowExW(dwExStyle, ClassName(), lpWindowName, dwStyle,
                                     x, y, nWidth, nHeight, hwndParent, hMenu, GetModuleHandle(nullptr), this);

            return (m_hwnd ? TRUE : FALSE);
        }

        [[nodiscard]] HWND Window() const { return m_hwnd; }
    protected:
        virtual void MessageLoop(UINT wMsgFilterMin, UINT wMsgFilterMax) {}
        [[nodiscard]] virtual PCWSTR ClassName() const = 0;
        virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
    };
}