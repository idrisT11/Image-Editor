#ifndef TOOLSWIDGET_H
#define TOOLSWIDGET_H

#include <QWidget>
#include "Popups/ResizePopup/resizepopup.h"
#include "Popups/LightenPopup/lightenpopup.h"

namespace Ui {
class ToolsWidget;
}

class ToolsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ToolsWidget(QWidget *parent = nullptr);
    ~ToolsWidget();
    QWidget *resizePopup;
    QWidget *lightenPopup;

private slots:
    void on_resizeButton_clicked();
    void on_lightenButton_clicked();

private:
    Ui::ToolsWidget *ui;
};

#endif // TOOLSWIDGET_H
