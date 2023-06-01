#include "dialog.h"
#include "ui_dialog.h"

const char PCF8591 = 0x48;
int fd;

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    if (wiringPiSetup () == -1) exit (1);
    fd = wiringPiI2CSetup(PCF8591);
    ui->setupUi(this);
    ui -> dial -> setDisabled(true);
    ui -> verticalSlider -> setDisabled(true);

    QTimer *tajmer = new QTimer(this);
    connect(tajmer,SIGNAL(timeout()),this,SLOT(prikazi_vrednosti()));
    tajmer -> start(1000);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::prikaz_vrednosti()
{
    float voltage,temperature;
    int lighting;

    wiringPiI2CReadReg8(fd, PCF8591 + 3) ; // dummy

    int adcVal = wiringPiI2CReadReg8(fd, PCF8591 + 3) ;
    voltage = adcVal * ( 3.3 / 255.0);

    ui -> dial -> setValue(voltage);

    lighting = wiringPiI2CReadReg8(fd, PCF8591 + 4) ;

    ui -> verticalSlider -> setValue(lighting);

    temperature = wiringPiI2CReadReg8(fd, PCF8591 + 2 ) ;
    ui -> lcdNumber ->display(temperature);

}


