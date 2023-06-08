#include "layeritemwidget.h"
#include "ui_layeritemwidget.h"

LayerItemWidget::LayerItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerItemWidget)
{
    ui->setupUi(this);
}

LayerItemWidget::~LayerItemWidget()
{
    delete ui;
}
