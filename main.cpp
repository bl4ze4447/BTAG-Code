/**
    Belu Antonie-Gabriel
    Last updated: 10/11/2023
    belutoni06@gmail.com
**/

#include "mainwin.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR pCmdLine, int nCmdShow) {
    auto app = new MWND::MainWindow(L"test-win");

    if (!app->Create(L"test-win", WS_OVERLAPPEDWINDOW))
        APP_RETURN_MACRO(STATUS::BAD::HWND_CREATION_FAILED, "Info", app->ID);

    ShowWindow(app->Window(), nCmdShow);
    app->MessageLoop(0, 0);

    APP_RETURN_MACRO(STATUS::OK::CLOSED_APP, "Info", 0);
}