#ifndef RESIZEPOPUP_H
#define RESIZEPOPUP_H

#include <QWidget>

namespace Ui {
class ResizePopup;
}

class ResizePopup : public QWidget
{
    Q_OBJECT

public:
    explicit ResizePopup(QWidget *parent = nullptr);
    ~ResizePopup();
    void init();

private slots:
    void on_CancelButton_clicked();
    void on_ApplyButton_clicked();
    void on_ScaleXInput_valueChanged(double arg1);
    void on_ScaleYInput_valueChanged(double arg1);

private:
    Ui::ResizePopup *ui;
    double scaleX;
    double scaleY;

signals:
    void Apply_Scale(double, double);
};

#endif // RESIZEPOPUP_H
