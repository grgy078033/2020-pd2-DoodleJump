#include <cstdlib>
#include "platform.h"
#include "platform_normal.h"


platform_normal::platform_normal()
{

}

void platform_normal::appear(){
    int props = rand()%100;
    if(props < 3){
        setPixmap(QPixmap(":/doodle jump png/prop(spring).png").scaled(70, 30));
        type = 2;
    }
    else if(props >= 3 && props < 6){
        setPixmap(QPixmap(":/doodle jump png/prop(rocket).png").scaled(70, 30));
        type = 3;
    }
    else{
        setPixmap(QPixmap(":/doodle jump png/platform(normal).png").scaled(70, 30));
        type = 0;
    }
    int rand_x = rand()%7;
    int rand_y = rand()%13;
    int pos_x = (rand_x*50);
    int pos_y = 40*rand_y+20;
    setPos(pos_x, pos_y);
}
