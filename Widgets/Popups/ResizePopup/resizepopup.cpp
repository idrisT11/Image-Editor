#include "resizepopup.h"
#include "ui_resizepopup.h"

ResizePopup::ResizePopup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResizePopup)
{
    ui->setupUi(this);
    scaleX = 1;
    scaleY = 1;
}

ResizePopup::~ResizePopup()
{
    delete ui;
}

void ResizePopup::init()
{
    ui->ScaleXInput->setValue(1);
    ui->ScaleYInput->setValue(1);
    scaleX = 1;
    scaleY = 1;
}

void ResizePopup::on_CancelButton_clicked()
{
    this->close();
}


void ResizePopup::on_ApplyButton_clicked()
{
    emit Apply_Scale(this->scaleX, this->scaleY);
    this->close();
}

void ResizePopup::on_ScaleXInput_valueChanged(double arg1)
{
    this->scaleX = arg1;
}


void ResizePopup::on_ScaleYInput_valueChanged(double arg1)
{
    this->scaleY = arg1;
}

