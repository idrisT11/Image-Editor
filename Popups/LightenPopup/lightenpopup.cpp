#include "lightenpopup.h"
#include "ui_lightenpopup.h"

LightenPopup::LightenPopup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LightenPopup)
{
    ui->setupUi(this);

    this->lightIntensity = 0.5;
}

LightenPopup::~LightenPopup()
{
    delete ui;
}

void LightenPopup::init()
{
    ui->lightenSlider->setValue(50);
    ui->LightenInput->setValue(0);
    this->lightIntensity = 0.5;
}

void LightenPopup::on_CancelButton_clicked()
{
    this->close();
}


void LightenPopup::on_ApplyButton_clicked()
{
    emit Apply_LightIntensity(this->lightIntensity * 255 * 2 - 255);
    this->close();
}

void LightenPopup::on_LightenInput_valueChanged(double arg1)
{
    this->lightIntensity = (arg1+100)/200;
    ui->lightenSlider->setValue(this->lightIntensity*100);
}


void LightenPopup::on_lightenSlider_valueChanged(int value)
{
    double dvalue = value / 100.0;

    this->lightIntensity = dvalue;
    ui->LightenInput->setValue(value*2-100);

    //emit Apply_LightIntensity(this->lightIntensity * 255 * 2 - 255);
}


