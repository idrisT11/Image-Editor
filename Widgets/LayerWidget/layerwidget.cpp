
#include "layerwidget.h"
#include "./ui_layerwidget.h"

LayerWidget::LayerWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::LayerWidget)
{
    ui->setupUi(this);
}

LayerWidget::~LayerWidget()
{
    delete ui;
}

