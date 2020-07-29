#ifndef PLATFORM_CRUSH_H
#define PLATFORM_CRUSH_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "platform.h"

class platform_crush : public platform
{
public:
    platform_crush();
    virtual void appear();
};

#endif // PLATFORM_CRUSH_H
