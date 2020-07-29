#include "mainwindow.h"
#include "dead.h"
#include "ui_dead.h"
extern int score;

dead::dead(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dead)
{
    ui->setupUi(this);
    ui->score->setNum(score);
    connect(ui->Confirm, SIGNAL(clicked()), this, SLOT(close()));
}

dead::~dead()
{
    delete ui;
}
