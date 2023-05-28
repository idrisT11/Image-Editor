#ifndef ERODEPOPUP_H
#define ERODEPOPUP_H

#include <QWidget>
#include "Classes/ImageTransformer/ImageTransformer.h"

namespace Ui {
class ErodePopup;
}

class ErodePopup : public QWidget
{
    Q_OBJECT

public:
    explicit ErodePopup(QWidget *parent = nullptr);
    ~ErodePopup();
    void init(bool model=DILATE_MODE);

    static const bool DILATE_MODE = true;
    static const bool ERODE_MODE = false;

private slots:
    void on_CancelButton_clicked();
    void on_ApplyButton_clicked();

    void on_kernelSizeInput_valueChanged(double arg1);

    void on_KernelRectRadio_clicked();
    void on_KernelCrossRadio_clicked();
    void on_KernelEllipseRadio_clicked();

private:
    Ui::ErodePopup *ui;
    int kernelSize;
    int kernelType;
    bool mode;

signals:
    void Apply_Erode(int, int);
    void Apply_Dilate(int, int);

};

#endif // ERODEPOPUP_H
