#include <cstdlib>
#include <ctime>
#include "dead.h"
#include "gen_platform.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QPalette>
#include <QBrush>
#include <QDebug>
int score = 0;
extern float b_x;
extern float b_y;
int monster_die = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(0, 0, 400, 600)),
    timer(new QTimer)
{
    srand(time(NULL));
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);

    background = new QGraphicsPixmapItem;
    background->setPixmap(QPixmap(":/doodle jump png/background.png").scaled(400,600));
    scene->addItem(background);
    background->setPos(0,0);

    player = new QGraphicsPixmapItem;
    player->setPixmap(QPixmap(":/doodle jump png/doodle(normal).png").scaled(50,50));
    scene->addItem(player);
    player->setPos(200-player->pixmap().width()/2, 450);
    timer->start(speed);
    connect(timer, SIGNAL(timeout()), this, SLOT(player_up()));

    monster = new QGraphicsPixmapItem;
    monster->setPixmap(QPixmap(":/doodle jump png/monster.png").scaled(100,70));
    scene->addItem(monster);
    monster->setPos((rand()%7)*50, -500);

    black_hole = new QGraphicsPixmapItem;
    black_hole->setPixmap(QPixmap(":/doodle jump png/hazard(black hole).png").scaled(100,100));
    scene->addItem(black_hole);
    black_hole->setPos((rand()%7)*50, -1000);

    for(int i = 0; i < 20; ++i){
        a[i] = gen_platform();
        a[i]->appear();
        scene->addItem(static_cast<QGraphicsPixmapItem*>(a[i]));
        if(i >= 1){
            for(int j = 0; j < i; ++j){
                if(i == j)
                    continue;
                if((a[j]->y() == a[i]->y()) && (a[i]->x() >= a[j]->x()-70 && a[i]->x() <= a[j]->x()+70)){
                    scene->removeItem(static_cast<QGraphicsPixmapItem*>(a[i]));
                    delete a[i];
                    --i;
                    break;
                }
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()) {
    case Qt::Key_P:
        timer->stop();
        break;
    case Qt::Key_R:
        timer->start(speed);
        break;
    case Qt::Key_U:
        if(speed_level < 8){
            speed -= 1;
            ++speed_level;
            ui->speed_count->setNum(speed_level);
        }
        break;
    case Qt::Key_L:
        if(speed_level > 1){
            speed += 1;
            --speed_level;
            ui->speed_count->setNum(speed_level);
        }
        break;
    case Qt::Key_A:
        player->setPos(player->x() - 29, player->y());
        if(player->x() < 0)
            player->setPos(350, player->y());
        break;
    case Qt::Key_D:
        player->setPos(player->x() + 29, player->y());
        if(player->x() > 350)
            player->setPos(0, player->y());
        break;
    case Qt::Key_Space:
        bullet *b = new bullet;
        b->setPixmap(QPixmap(":/doodle jump png/bullet.png").scaled(10, 20));
        b->setPos(player->x() + player->pixmap().width() / 2 - b->pixmap().width() / 2, player->y() - b->pixmap().height());
        scene->addItem(b);
        connect(timer, SIGNAL(timeout()), b, SLOT(fly()));
        break;
    }
}

void MainWindow::player_down(){
    timer->start(speed);
    if(b_y >= player->y()-150){
        player->setPixmap(QPixmap(":/doodle jump png/doodle(shooting).png").scaled(55,75));
    }
    else {
        player->setPixmap(QPixmap(":/doodle jump png/doodle(normal).png").scaled(50,50));
    }
    if((b_x >= monster->x() && b_x <= monster->x()+100) && (b_y >= monster->y() && b_y <= monster->y()+70)){
        scene->removeItem(static_cast<QGraphicsPixmapItem*>(monster));
        delete monster;
        monster = new QGraphicsPixmapItem;
        monster->setPixmap(QPixmap(":/doodle jump png/monster.png").scaled(100,70));
        scene->addItem(monster);
        monster->setPos((rand()%7)*50, -700);
        monster_die = 1;
    }
    player->setPos(player->x(), player->y()+0.06*player_down_count);
    if(player->y() >= 575){
        gameover();
    }
    if((player->x() >= monster->x()-40 && player->x() <= monster->x()+100) && (player->y() >= monster->y()-50 && player->y() <= monster->y()+60)){
        gameover();
    }
    if((player->x() >= black_hole->x()-40 && player->x() <= black_hole->x()+90) && (player->y() >= black_hole->y()-40 && player->y() <= black_hole->y()+80)){
        gameover();
    }
    player_down_count += 1;
    for(int i = 0; i < 20; ++i){
        if((player->y()+40 >= a[i]->y() && player->y()+40 <= a[i]->y()+10) && (player->x() >= a[i]->x()-20 && player->x() <= a[i]->x()+53)){
            if(a[i]->type == 1){
                scene->removeItem(static_cast<QGraphicsPixmapItem*>(a[i]));
                delete a[i];
                a[i] = gen_platform();
                a[i]->appear();
                a[i]->setPos(a[i]->x(), -50);
                scene->addItem(static_cast<QGraphicsPixmapItem*>(a[i]));
            }
            else if(a[i]->type == 2){
                player_up_count = -30;
                player_down_count = 0;
                disconnect(timer, SIGNAL(timeout()), this, SLOT(player_down()));
                connect(timer, SIGNAL(timeout()), this, SLOT(player_up()));
                break;
            }
            else if(a[i]->type == 3){
                player_up_count = -150;
                player_down_count = 0;
                disconnect(timer, SIGNAL(timeout()), this, SLOT(player_down()));
                connect(timer , SIGNAL(timeout()), this, SLOT(rocket_up()));
                break;
            }
            else {
                player_up_count = 0;
                player_down_count = 0;
                disconnect(timer, SIGNAL(timeout()), this, SLOT(player_down()));
                connect(timer, SIGNAL(timeout()), this, SLOT(player_up()));
                break;
            }
        }
    }
}
void MainWindow::player_up(){
    timer->start(speed);
    if(b_y >= player->y()-150){
        player->setPixmap(QPixmap(":/doodle jump png/doodle(shooting).png").scaled(55,75));
    }
    else {
        player->setPixmap(QPixmap(":/doodle jump png/doodle(normal).png").scaled(50,50));
    }
    if((b_x >= monster->x() && b_x <= monster->x()+100) && (b_y >= monster->y() && b_y <= monster->y()+70)){
        scene->removeItem(static_cast<QGraphicsPixmapItem*>(monster));
        delete monster;
        monster = new QGraphicsPixmapItem;
        monster->setPixmap(QPixmap(":/doodle jump png/monster.png").scaled(100,70));
        scene->addItem(monster);
        monster->setPos((rand()%7)*50, -700);
        monster_die = 1;
    }
    for(int i = 0; i < 20; ++i){
        if((player->y()+40 >= a[i]->y() && player->y()+40 <= a[i]->y()+40) && (player->x() >= a[i]->x()-20 && player->x() <= a[i]->x()+53)){
            if(a[i]->type == 3){
                player_up_count = 0;
                player_down_count = 0;
                connect(timer, SIGNAL(timeout()), this, SLOT(rocket_up()));
                disconnect(timer, SIGNAL(timeout()), this, SLOT(player_up()));
            }
        }
    }
    player_up_y = 5.97-0.06*player_up_count;
    player->setPos(player->x(), player->y()-player_up_y);
    if((player->x() >= monster->x()-40 && player->x() <= monster->x()+100) && (player->y() >= monster->y()-50 && player->y() <= monster->y()+60)){
        gameover();
    }
    if((player->x() >= black_hole->x()-40 && player->x() <= black_hole->x()+90) && (player->y() >= black_hole->y()-40 && player->y() <= black_hole->y()+80)){
        gameover();
    }
    player_up_count += 1;
    if(player_up_count == 100){
        connect(timer, SIGNAL(timeout()), this, SLOT(player_down()));
        disconnect(timer, SIGNAL(timeout()), this, SLOT(player_up()));
        player_up_count = -150;
        player_down_count = 0;
    }
    if(player->y() <= 250){
        player->setPos(player->x(), player->y()+player_up_y);
        score += player_up_y;
        ui->score_count->setNum(score);
        monster->setPos(monster->x(), monster->y()+player_up_y);
        if(monster->y() >= 570){
            scene->removeItem(static_cast<QGraphicsPixmapItem*>(monster));
            delete monster;
            monster = new QGraphicsPixmapItem;
            monster->setPixmap(QPixmap(":/doodle jump png/monster.png").scaled(100,70));
            scene->addItem(monster);
            monster->setPos((rand()%7)*50, -700);
        }
        black_hole->setPos(black_hole->x(), black_hole->y()+player_up_y);
        if(black_hole->y() >= 570){
            scene->removeItem(static_cast<QGraphicsPixmapItem*>(black_hole));
            delete black_hole;
            black_hole = new QGraphicsPixmapItem;
            black_hole->setPixmap(QPixmap(":/doodle jump png/hazard(black hole).png").scaled(100,100));
            scene->addItem(black_hole);
            black_hole->setPos((rand()%7)*50, -1500);
        }
        for(int i = 0; i < 20; ++i){
            a[i]->setPos(a[i]->x(), a[i]->y()+player_up_y);
            if(a[i]->y() >= 570){
                scene->removeItem(static_cast<QGraphicsPixmapItem*>(a[i]));
                delete a[i];
                a[i] = gen_platform();
                a[i]->appear();
                a[i]->setPos(a[i]->x(), -50);
                scene->addItem(static_cast<QGraphicsPixmapItem*>(a[i]));

            }
        }
    }
}
void MainWindow::rocket_up(){
    timer->start(speed);
    if((b_x >= monster->x() && b_x <= monster->x()+100) && (b_y >= monster->y() && b_y <= monster->y()+70)){
        scene->removeItem(static_cast<QGraphicsPixmapItem*>(monster));
        delete monster;
        monster = new QGraphicsPixmapItem;
        monster->setPixmap(QPixmap(":/doodle jump png/monster.png").scaled(100,70));
        scene->addItem(monster);
        monster->setPos((rand()%7)*50, -700);
        monster_die = 1;
    }
    player->setPixmap(QPixmap(":/doodle jump png/doodle(rocket).png").scaled(70,70));
    player_up_y = 10;
    player->setPos(player->x(), player->y()-player_up_y);
    player_up_count += 1;
    if(player_up_count == 100){
        connect(timer, SIGNAL(timeout()), this, SLOT(player_up()));
        disconnect(timer, SIGNAL(timeout()), this, SLOT(rocket_up()));
        player_up_count = 0;
        player_down_count = 0;
    }
    if(player->y() <= 250){
        player->setPos(player->x(), player->y()+player_up_y);
        score += player_up_y;
        ui->score_count->setNum(score);
        monster->setPos(monster->x(), monster->y()+player_up_y);
        if(monster->y() >= 570){
            scene->removeItem(static_cast<QGraphicsPixmapItem*>(monster));
            delete monster;
            monster = new QGraphicsPixmapItem;
            monster->setPixmap(QPixmap(":/doodle jump png/monster.png").scaled(100,70));
            scene->addItem(monster);
            monster->setPos((rand()%7)*50, -500);
        }
        black_hole->setPos(black_hole->x(), black_hole->y()+player_up_y);
        if(black_hole->y() >= 570){
            scene->removeItem(static_cast<QGraphicsPixmapItem*>(black_hole));
            delete black_hole;
            black_hole = new QGraphicsPixmapItem;
            black_hole->setPixmap(QPixmap(":/doodle jump png/hazard(black hole).png").scaled(100,100));
            scene->addItem(black_hole);
            black_hole->setPos((rand()%7)*50, -1500);
        }
        for(int i = 0; i < 20; ++i){
            a[i]->setPos(a[i]->x(), a[i]->y()+player_up_y);
            if(a[i]->y() >= 570){
                scene->removeItem(static_cast<QGraphicsPixmapItem*>(a[i]));
                delete a[i];
                a[i] = gen_platform();
                a[i]->appear();
                a[i]->setPos(a[i]->x(), -50);
                scene->addItem(static_cast<QGraphicsPixmapItem*>(a[i]));

            }
        }
    }
}
void MainWindow::gameover(){
    timer->stop();
    if(score > record){
        record = score;
        ui->record->setNum(record);
    }
    dead dead;
    dead.setModal(true);
    dead.exec();
    score = 0;
    ui->score_count->setNum(score);

    player->setPos(200-player->pixmap().width()/2, 300);
    monster->setPos((rand()%7)*50, -500);
    black_hole->setPos((rand()%7)*50, -1000);
    for(int i = 0; i < 20; ++i){
        delete a[i];
    }
    for(int i = 0; i < 20; ++i){
        a[i] = gen_platform();
        a[i]->appear();
        scene->addItem(static_cast<QGraphicsPixmapItem*>(a[i]));
        if(i >= 1){
            for(int j = 0; j < i; ++j){
                if(i == j)
                    continue;
                if((a[j]->y() == a[i]->y()) && (a[i]->x() >= a[j]->x()-70 && a[i]->x() <= a[j]->x()+70)){
                    scene->removeItem(static_cast<QGraphicsPixmapItem*>(a[i]));
                    delete a[i];
                    --i;
                    break;
                }
            }
        }
    }
}
