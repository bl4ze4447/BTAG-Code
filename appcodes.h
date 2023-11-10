#pragma once
#define FAULTY_CODES_START (-5)
#define _LAEXPLORER_DEBUG_MODE

typedef short STATUS_T;

class STATUS {
public:
    enum OK { // 0
        CLOSED_BY_USER = 0,
        D2D1_FACTORY_CREATED = 0,
    };
    static const int DEFAULT = 1; // 1
    enum BAD { // < 0
        HWND_CREATION_FAILED = FAULTY_CODES_START,
        WINDOW_CREATION_FAILED,
        INVALID_FILE,
        INVALID_DSIZE,
        INVALID_PARAMETER,
    };
};