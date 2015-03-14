#ifndef SETTINGS
#define SETTINGS

#include <QtGlobal>

struct Settings {
    int startingOffset;
    int endingOffset;
    int incrementMinNum;
    int incrementMaxNum;
    bool random;
    bool add;
    bool shiftLeft;
    bool replace;
    int addNum;
    int shiftLeftNum;
    int replaceMinNum;
    int replaceMaxNum;
};

#endif // SETTINGS

