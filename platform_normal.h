#ifndef PLATFORM_NORMAL_H
#define PLATFORM_NORMAL_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "platform.h"

class platform_normal : public platform
{
public:
    platform_normal();
    virtual void appear();
};

#endif // PLATFORM_NORMAL_H
