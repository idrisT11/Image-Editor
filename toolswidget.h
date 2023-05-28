#ifndef TOOLSWIDGET_H
#define TOOLSWIDGET_H

#include <QWidget>
#include "Popups/ResizePopup/resizepopup.h"
#include "Popups/LightenPopup/lightenpopup.h"
#include "Popups/CannyPopup/cannypopup.h"
#include "Popups/ErodePopup/erodepopup.h"

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
    ErodePopup * erodePopup;

private slots:
    void on_resizeButton_clicked();
    void on_lightenButton_clicked();
    void on_pushButton_3_clicked();
    void on_dilateButton_clicked();
    void on_erodeButton_clicked();
    void on_blurButton_clicked();

    void on_sobelButton_clicked();

private:
    Ui::ToolsWidget *ui;

signals:
    void Apply_Filter(int);

};

#endif // TOOLSWIDGET_H
