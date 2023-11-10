/**
    Belu Antonie-Gabriel
    Last updated: 10/11/2023
    belutoni06@gmail.com
**/

#include "mainwin.h"

HRESULT MWND::MainWindow::CreateGraphicsResources() {
    HRESULT hResult = S_OK;
    if (pRenderTarget == nullptr) {
        RECT rect;
        GetClientRect(m_hwnd, &rect);
        D2D1_SIZE_U size = D2D1::SizeU(rect.right, rect.bottom);

        hResult = pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
                                                   D2D1::HwndRenderTargetProperties(m_hwnd, size),
                                                   &pRenderTarget);

        if (SUCCEEDED(hResult)) LOG("MainWindow::CreateGraphicsResources", "Created graphics resources",          "Info",  ID)
        else                    LOG("MainWindow::CreateGraphicsResources", "Failed to create graphics resources", "ERROR", ID)
    }

    return hResult;
}

void MWND::MainWindow::DiscardGraphicsResources() {
    SafeRelease(&pRenderTarget);
    SafeRelease(&pBrush);
    LOG("MainWindow::DiscardGraphicsResources", "Discarded graphics resources", "Info", ID)
}

void MWND::MainWindow::OnPaint() {
    HRESULT hResult = CreateGraphicsResources();
    if (SUCCEEDED(hResult)) {
        PAINTSTRUCT pStruct;
        BeginPaint(m_hwnd, &pStruct);

        pRenderTarget->BeginDraw();
        pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

        if (pDWriteFactory == nullptr)
            hResult = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
                                          __uuidof(IDWriteFactory),
                                          reinterpret_cast<IUnknown **>(&pDWriteFactory));

        if (FAILED(hResult))
            LOG("MainWindow::OnPaint()::DWriteCreateFactory", "Could not create DWriteFactory", "Error", ID)
        else {
            // Formatting happens here, this is just for testing purposes
            IDWriteTextFormat *pTextFormat;

            pDWriteFactory->CreateTextFormat(
                    L"Arial",
                    nullptr,
                    DWRITE_FONT_WEIGHT_REGULAR,
                    DWRITE_FONT_STYLE_NORMAL,
                    DWRITE_FONT_STRETCH_NORMAL,
                    24,
                    L"en-us",
                    &pTextFormat
            );

            const D2D1_COLOR_F color = D2D1::ColorF(D2D1::ColorF::White);
            pRenderTarget->CreateSolidColorBrush(color, &pBrush);
            pRenderTarget->DrawTextW(
                    fContent.c_str(),
                    fContent.length(),
                    pTextFormat,
                    D2D1::RectF(static_cast<float>(fRect.left),
                                static_cast<float>(fRect.top),
                                static_cast<float>(fRect.right),
                                static_cast<float>(fRect.bottom)),
                    pBrush);
            LOG("MainWindow::OnPaint()::pRenderTarget->DrawTextW()", "Draw given wstring", "Info", ID)
        }

        hResult = pRenderTarget->EndDraw();
        if (FAILED(hResult) || hResult == D2DERR_RECREATE_TARGET) {
            LOG("MainWindow::OnPaint", "pRenderTarget->EndDraw() failed", "Warning", ID)
            DiscardGraphicsResources();
        }

        EndPaint(m_hwnd, &pStruct);
    }
}

void MWND::MainWindow::Resize() {
    if (pRenderTarget != nullptr) {
        RECT rect;
        GetClientRect(m_hwnd, &rect);

        D2D1_SIZE_U size = D2D1::SizeU(rect.right, rect.bottom);
        fRect = D2D1::RectU(rect.left, rect.top, rect.right, rect.bottom);

        pRenderTarget->Resize(size);
        InvalidateRect(m_hwnd, nullptr, FALSE);
        LOG("MainWindow::Resize", "Client resized", "Info", ID)
    }
}

LRESULT MWND::MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            if (FAILED(D2D1CreateFactory(
                    D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory
            ))) APP_RETURN_MACRO(STATUS::BAD::WINDOW_CREATION_FAILED, "Error", ID); // CreateWindowEx is at fault

            RECT rect; GetClientRect(m_hwnd, &rect); fRect = D2D1::RectU(rect.left, rect.top, rect.right, rect.bottom);
            LOG("MainWindow::HandleMessage", "Created D2D1 factory", "Info", ID)
            APP_RETURN_MACRO(STATUS::OK::D2D1_FACTORY_CREATED, "Info", ID);

        case WM_DESTROY:
            LOG("MainWindow::HandleMessage", "WM_Destroy", "Info", ID)
            DiscardGraphicsResources();
            SafeRelease(&pFactory);
            SafeRelease(&pDWriteFactory);
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:
            OnPaint();
            return 0;

        case WM_SIZE:
            Resize();
            return 0;

        case WM_CHAR: {
            // Just testing drawing
            wchar_t keyStr[32];
            int result = GetKeyNameTextW(lParam, keyStr, 32);
            memcpy(keyStr, keyStr, result);
            if (wcscmp(keyStr, L"Space") == 0) fContent += L" ";
            else if (wcscmp(keyStr, L"Backspace") == 0) fContent = fContent.substr(0, fContent.length() - 1);
            else fContent += keyStr;
            SendMessageW(Window(), WM_PAINT, wParam, lParam);
            return 0;
        }

        default:
            return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
}

void MWND::MainWindow::MessageLoop(UINT wMsgFilterMin, UINT wMsgFilterMax) {
    MSG msg{};
    while (GetMessage(&msg, nullptr, wMsgFilterMin, wMsgFilterMax)) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
}