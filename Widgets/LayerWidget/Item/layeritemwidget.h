#ifndef LAYERITEMWIDGET_H
#define LAYERITEMWIDGET_H

#include <QWidget>

namespace Ui {
class LayerItemWidget;
}

class LayerItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LayerItemWidget(QWidget *parent = nullptr);
    ~LayerItemWidget();

private:
    Ui::LayerItemWidget *ui;
};

#endif // LAYERITEMWIDGET_H
