#include "mainwin.h"
#include <iostream>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pCmdLine, int nCmdShow) {
    auto app = MWND::MainWindow(L"test-win");
    auto app2 = MWND::MainWindow(L"test-win2");

    if (!app.Create(L"test-win", WS_OVERLAPPEDWINDOW))
        APP_RETURN_MACRO(STATUS::BAD::HWND_CREATION_FAILED); // Changes functionality if _LAEXPLORER_DEBUG_MODE is defined in "appcodes.h"

    if (!app2.Create(L"test-win", WS_OVERLAPPEDWINDOW))
        APP_RETURN_MACRO(STATUS::BAD::HWND_CREATION_FAILED); // Changes functionality if _LAEXPLORER_DEBUG_MODE is defined in "appcodes.h"

    ShowWindow(app.Window(), nCmdShow);
    app.MessageLoop(0, 0);
    ShowWindow(app2.Window(), nCmdShow);
    app2.MessageLoop(0, 0);

    APP_RETURN_MACRO(STATUS::OK::CLOSED_BY_USER);
}