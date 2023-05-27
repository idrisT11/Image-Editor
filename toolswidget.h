#ifndef TOOLSWIDGET_H
#define TOOLSWIDGET_H

#include <QWidget>
#include "Popups/ResizePopup/resizepopup.h"
#include "Popups/LightenPopup/lightenpopup.h"
#include "Popups/CannyPopup/cannypopup.h"

namespace Ui {
class ToolsWidget;
}

class ToolsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ToolsWidget(QWidget *parent = nullptr);
    ~ToolsWidget();
    ResizePopup *resizePopup;
    LightenPopup *lightenPopup;
    CannyPopup *cannyPopup;

private slots:
    void on_resizeButton_clicked();
    void on_lightenButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::ToolsWidget *ui;
};

#endif // TOOLSWIDGET_H
