#ifndef DEAD_H
#define DEAD_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class dead;
}

class dead : public QDialog
{
    Q_OBJECT

public:
    explicit dead(QWidget *parent = nullptr);
    ~dead();

private:
    Ui::dead *ui;
};

#endif // DEAD_H
