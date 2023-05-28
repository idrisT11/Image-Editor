#include "toolswidget.h"
#include "ui_toolswidget.h"

ToolsWidget::ToolsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolsWidget)
{
    ui->setupUi(this);

    resizePopup = new ResizePopup;
    lightenPopup = new LightenPopup;
    cannyPopup = new CannyPopup;
    erodePopup = new ErodePopup;
}

ToolsWidget::~ToolsWidget()
{
    delete ui;
}

void ToolsWidget::on_resizeButton_clicked()
{
    resizePopup->show();
    resizePopup->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    resizePopup->resize(368,118);
    resizePopup->init();
}


void ToolsWidget::on_lightenButton_clicked()
{
    lightenPopup->show();
    lightenPopup->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    lightenPopup->resize(400,267-100);
    lightenPopup->init();
}


void ToolsWidget::on_pushButton_3_clicked()
{
    cannyPopup->show();
    cannyPopup->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    cannyPopup->resize(400,267-100);
    cannyPopup->init();
}

void ToolsWidget::on_erodeButton_clicked()
{
    erodePopup->show();
    erodePopup->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    erodePopup->resize(400,267-100);
    erodePopup->init(ErodePopup::ERODE_MODE);
}

void ToolsWidget::on_dilateButton_clicked()
{
    erodePopup->show();
    erodePopup->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    erodePopup->resize(400,267-100);
    erodePopup->init(ErodePopup::DILATE_MODE);
}




