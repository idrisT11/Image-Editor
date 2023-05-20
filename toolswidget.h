#ifndef TOOLSWIDGET_H
#define TOOLSWIDGET_H

#include <QWidget>
#include "Popups/ResizePopup/resizepopup.h"

namespace Ui {
class ToolsWidget;
}

class ToolsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ToolsWidget(QWidget *parent = nullptr);
    ~ToolsWidget();
    QWidget *popup;

private slots:
    void on_pushButton_clicked();

private:
    Ui::ToolsWidget *ui;
};

#endif // TOOLSWIDGET_H
