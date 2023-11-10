/**
    Belu Antonie-Gabriel
    Last updated: 10/11/2023
    belutoni06@gmail.com
**/

#pragma once

class STATUS {
public:
    enum OK { // > 0
        CLOSED_WINDOW = 1,
        CLOSED_APP,
        D2D1_FACTORY_CREATED,
    };
    const int AWAITING = 0; // 0
    enum BAD { // >= 128 && <= -1
        HWND_CREATION_FAILED = -128,
        WINDOW_CREATION_FAILED,
    };
};