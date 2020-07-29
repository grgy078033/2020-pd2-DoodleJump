#include <cstdlib>
#include "platform.h"
#include "platform_crush.h"


platform_crush::platform_crush()
{

}

void platform_crush::appear(){
    setPixmap(QPixmap(":/doodle jump png/platform(crush).png").scaled(70, 30));
    int rand_x = rand()%7;
    int rand_y = rand()%13;
    int pos_x = (rand_x*50);
    int pos_y = 40*rand_y+20;
    setPos(pos_x, pos_y);
    type = 1;
}
