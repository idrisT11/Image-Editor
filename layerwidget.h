
#ifndef LAYERWIDGET_H
#define LAYERWIDGET_H

#include <QWidget>
#include "./ui_layerwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LayerWidget; }
QT_END_NAMESPACE

class LayerWidget : public QWidget
{
    Q_OBJECT

public:
    LayerWidget(QWidget *parent = nullptr);
    ~LayerWidget();

private:
    Ui::LayerWidget *ui;
};

#endif // LAYERWIDGET_H
