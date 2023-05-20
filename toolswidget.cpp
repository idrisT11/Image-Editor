#include "toolswidget.h"
#include "ui_toolswidget.h"

ToolsWidget::ToolsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolsWidget)
{
    ui->setupUi(this);

    popup = new ResizePopup;

    //QWidget *w = new QWidget;
    //w->show();
}

ToolsWidget::~ToolsWidget()
{
    delete ui;
}

void ToolsWidget::on_pushButton_clicked()
{
    popup->show();
    popup->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    popup->resize(368,118);
}

