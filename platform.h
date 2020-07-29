#ifndef PLATFORM_H
#define PLATFORM_H
#include <cstdlib>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class platform : public QObject, public QGraphicsPixmapItem
{
public:
    platform();
    virtual void appear() = 0;
    int type;
};

#endif // PLATFORM_H
