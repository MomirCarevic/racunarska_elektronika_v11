#include "dialog.h"
#include "ui_dialog.h"

int fd = -1, ret;
char *tmp1, tmp2[10], ch='t';
char devname_head[50] = "/sys/bus/w1/devices/28-00000";
char devname_number[10] = "0000000";                        // <<<<<=========== potrebno upisati onaj broj uredjaja
char devname_end[10] = "/w1_slave";
char dev_name[100];
long value;
int integer, decimal;
char buffer[100];
int i,j;

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    wiringPiSetup();

    QTimer *tajmer = new  QTimer(this);
    connect(tajmer,SIGNAL(timeout()),this,SLOT(showTemp()));
    tajmer -> start(1000);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::showTemp()
{
    strcpy(dev_name, devname_head);
    strcat(dev_name, devname_number);
    strcat(dev_name, devname_end);
    /*if ((fd = open(dev_name, O_RDONLY)) < 0)
    {
        perror("Greška pri otvaranju!");
        exit(1);
    }*/

    ret = read(fd, buffer, sizeof(buffer));

    if (ret < 0) {
        perror("Greška pri čitanju!");
        exit(1);
    }



        tmp1 = strchr(buffer, ch);
        sscanf(tmp1, "t=%s", tmp2);
        value = atoi(tmp2);
        integer = value / 1000;
        decimal = value % 1000;

        printf("Temperatura je %d.%d\n", integer,decimal);

        ui -> lcdNumber -> display(decimal);
}



