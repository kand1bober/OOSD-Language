#ifndef PROJECT_PROC_ENUM_HEADER
#define PROJECT_PROC_ENUM_HEADER

enum Commands
{
    kNull = 0,
    kAX = 1,
    kBX = 2,
    kCX = 3,
    kDX = 4,
    kPush = 5,
    kPop = 6,
    kOut = 7,
    kAdd = 8,
    kIn = 9,
    kSub = 10,
    kMul = 11,
    kDiv = 12,
    kRoot = 13,
    kSin = 14,
    kCos = 15,
    kDump = 16,
    kHlt = 17,

    kJa = 18,
    kJae = 19,
    kJb = 20,
    kJbe = 21,
    kJe = 22,
    kJne = 23,
    kJmp = 24,
    kJmpspace = 25,

    kCall = 26,
    kRet = 27,
    kDraw = 28,
    kFloor = 29,
};



const unsigned char MEMORY_MASK = 128;
const unsigned char REGISTER_MASK = 64;
const unsigned char INPUT_MASK = 32;


#endif
