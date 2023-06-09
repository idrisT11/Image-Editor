#ifndef TOOLSWIDGET_H
#define TOOLSWIDGET_H

#include <QWidget>
#include "Widgets/Popups/ResizePopup/resizepopup.h"
#include "Widgets/Popups/LightenPopup/lightenpopup.h"
#include "Widgets/Popups/CannyPopup/cannypopup.h"
#include "Widgets/Popups/ErodePopup/erodepopup.h"

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
    void on_facialButton_clicked();

private:
    Ui::ToolsWidget *ui;

signals:
    void Apply_Filter(int);
    void Apply_Face_Recognition();

};

#endif // TOOLSWIDGET_H
