#include "toolswidget.h"
#include "ui_toolswidget.h"

ToolsWidget::ToolsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolsWidget)
{
    ui->setupUi(this);
}

ToolsWidget::~ToolsWidget()
{
    delete ui;
}
