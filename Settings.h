#ifndef SETTINGS
#define SETTINGS

#include <QtGlobal>

//Allowing files to be larger than this size won't allow users to properly manipulate the start and end offsets
const int MAX_FILE_SIZE = 999999999;

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
    int replaceOldNum;
    int replaceNewNum;
};

#endif // SETTINGS

