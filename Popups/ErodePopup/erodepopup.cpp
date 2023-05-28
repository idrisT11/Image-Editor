#include "erodepopup.h"
#include "ui_erodepopup.h"

ErodePopup::ErodePopup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ErodePopup)
{
    ui->setupUi(this);
}

ErodePopup::~ErodePopup()
{
    delete ui;
}

void ErodePopup::init(bool o_mode)
{
    this->kernelSize = 3;
    this->kernelType = ImageTransformer::MATHMORPH_ELLIPSE;
    this->mode = o_mode;

    if (this->mode == ErodePopup::DILATE_MODE)

        this->setWindowTitle("Dilate");
    else

        this->setWindowTitle("Erode");
}

void ErodePopup::on_CancelButton_clicked()
{
    this->close();
}

void ErodePopup::on_ApplyButton_clicked()
{
    if (this->mode == ErodePopup::DILATE_MODE)

        emit Apply_Dilate(this->kernelType, this->kernelSize);
    else

        emit Apply_Erode(this->kernelType, this->kernelSize);

    this->close();
}

void ErodePopup::on_kernelSizeInput_valueChanged(double arg1)
{
    this->kernelSize = arg1;
}

void ErodePopup::on_KernelRectRadio_clicked()
{
    this->kernelType = ImageTransformer::MATHMORPH_RECT;
}

void ErodePopup::on_KernelCrossRadio_clicked()
{
    this->kernelType = ImageTransformer::MATHMORPH_CROSS;
}

void ErodePopup::on_KernelEllipseRadio_clicked()
{
    this->kernelType = ImageTransformer::MATHMORPH_ELLIPSE;
}

