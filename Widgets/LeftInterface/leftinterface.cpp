#include "leftinterface.h"
#include "./ui_leftinterface.h"

LeftInterface::LeftInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LeftInterface)
{
    ui->setupUi(this);
}

LeftInterface::~LeftInterface()
{
    delete ui;
}
