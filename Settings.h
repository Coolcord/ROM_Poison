#ifndef SETTINGS
#define SETTINGS

#include <QtGlobal>

struct Settings {
    qint64 startingOffset;
    qint64 endingOffset;
    qint64 incrementMinNum;
    qint64 incrementMaxNum;
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

