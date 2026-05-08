#include "RandomUtil.h"
#include <cstdlib>
#include <ctime>

int RandomUtil::random(int min, int max)
{
    static bool init = false;
    if (!init) { srand((unsigned)time(NULL)); init = true; }
    return min + rand() % (max - min + 1);
}

float RandomUtil::random(float min, float max)
{
    static bool init = false;
    if (!init) { srand((unsigned)time(NULL)); init = true; }
    float r = (float)rand() / RAND_MAX;
    return min + r * (max - min);
}