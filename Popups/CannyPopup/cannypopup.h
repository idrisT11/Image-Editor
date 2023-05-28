#ifndef CANNYPOPUP_H
#define CANNYPOPUP_H

#include <QWidget>

namespace Ui {
class cannyPopup;
}

class CannyPopup : public QWidget
{
    Q_OBJECT

public:
    explicit CannyPopup(QWidget *parent = nullptr);
    ~CannyPopup();
    void init();

private slots:
    void on_CancelButton_clicked();
    void on_ApplyButton_clicked();

    void on_LowThresholdInput_valueChanged(double arg1);
    void on_HighThresholdInput_valueChanged(double arg1);

    void on_Kernel5Radio_clicked();
    void on_Kernel3Radio_clicked();
    void on_Kernel7Radio_clicked();


private:
    Ui::cannyPopup *ui;
    double lowThreshold;
    double highThreshold;
    int kernelSize;

signals:
    void Apply_Canny(double, double, int);
};

#endif // CANNYPOPUP_H
