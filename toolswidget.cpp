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

