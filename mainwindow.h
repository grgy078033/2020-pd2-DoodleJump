#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "platform.h"
#include "bullet.h"

#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void gameover();

public slots:
    virtual void keyPressEvent(QKeyEvent *e);
    void player_up();
    void player_down();
    void rocket_up();
private:
    Ui::MainWindow *ui;
    double player_up_y;
    int player_up_count = 0;
    double player_down_y;
    int player_down_count = 0;
    int speed = 8;
    int speed_level = 1;
    int record = 0;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *background;
    QGraphicsPixmapItem *player;
    QGraphicsPixmapItem *monster;
    QGraphicsPixmapItem *black_hole;
    platform *a[20];
    QTimer *timer;
};

#endif // MAINWINDOW_H
