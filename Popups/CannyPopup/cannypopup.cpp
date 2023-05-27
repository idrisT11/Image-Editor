#include "cannypopup.h"
#include "ui_cannypopup.h"

CannyPopup::CannyPopup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cannyPopup)
{
    ui->setupUi(this);
}

CannyPopup::~CannyPopup()
{
    delete ui;
}

void CannyPopup::init()
{
    this->kernelSize = 3;
    this->lowThreshold = 50;
    this->highThreshold = 151;
}

void CannyPopup::on_CancelButton_clicked()
{
    this->close();
}


void CannyPopup::on_ApplyButton_clicked()
{
    emit Apply_Canny(this->lowThreshold, this->highThreshold, this->kernelSize);
    this->close();
}


void CannyPopup::on_LowThresholdInput_valueChanged(double arg1)
{
    this->lowThreshold = arg1;
}


void CannyPopup::on_HighThresholdInput_valueChanged(double arg1)
{
    this->highThreshold = arg1;
}

void CannyPopup::on_Kernel3Radio_clicked()
{
    this->kernelSize = 3;
}


void CannyPopup::on_Kernel5Radio_clicked()
{
    this->kernelSize = 5;
}




void CannyPopup::on_Kernel7Radio_clicked()
{
    this->kernelSize = 7;
}


void CannyPopup::on_Kernel11Radio_clicked()
{
    this->kernelSize = 11;
}

