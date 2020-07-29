#include <cstdlib>
#include "gen_platform.h"
#define NUM_PLATFORM 3
#define NORMAL_A 0
#define NORMAL_B 1
#define CRUSH 2

platform *gen_platform(){
    int platform_type;
    platform *ptr;

    platform_type = random()%NUM_PLATFORM;

    switch (platform_type) {
        case NORMAL_A:
            ptr = new platform_normal;
            break;
        case NORMAL_B:
            ptr = new platform_normal;
            break;
        case CRUSH:
            ptr = new platform_crush;
            break;
    }
    return ptr;
}
