#ifndef LIGHTENPOPUP_H
#define LIGHTENPOPUP_H

#include <QWidget>

namespace Ui {
class LightenPopup;
}

class LightenPopup : public QWidget
{
    Q_OBJECT

public:
    explicit LightenPopup(QWidget *parent = nullptr);
    ~LightenPopup();

private slots:
    void on_LightenInput_valueChanged(double arg1);
    void on_lightenSlider_valueChanged(int value);

    void on_CancelButton_clicked();

    void on_ApplyButton_clicked();

private:
    Ui::LightenPopup *ui;
    double lightIntensity;

signals:
    void Apply_LightIntensity(double);
};

#endif // LIGHTENPOPUP_H
