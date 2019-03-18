#ifndef SETTINGS
#define SETTINGS

#include <QtGlobal>

//Allowing files to be larger than this size won't allow users to properly manipulate the start and end offsets
const static int MAX_FILE_SIZE = 999999999;

struct Settings {
    qint64 startingOffset;
    qint64 endingOffset;
    qint64 incrementMinNum;
    qint64 incrementMaxNum;
    bool increment;
    bool random;
    bool add;
    bool shiftLeft;
    bool replace;
    int addNum;
    int shiftLeftNum;
    int replaceOldNum;
    int replaceNewNum;
};

#endif // SETTINGS

