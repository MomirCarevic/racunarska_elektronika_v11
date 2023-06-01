#include <unistd.h>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>

#include <QTime>
#include <QTimer>
#include <QDial>
#include <QSlider>

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void prikaz_vrednosti();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
