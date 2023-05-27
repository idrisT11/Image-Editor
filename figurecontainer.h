#ifndef FIGURECONTAINER_H
#define FIGURECONTAINER_H

#include <QWidget>
#include <QMouseEvent>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

namespace Ui {
class FigureContainer;
}

class FigureContainer : public QWidget
{
    Q_OBJECT

public:
    explicit FigureContainer(QWidget *parent = nullptr);
    ~FigureContainer();

private slots:
    void Mouse_current_pos();
    void Mouse_left_click();
    void Mouse_left_up();
    void ResizeConfirmed(double scaleX, double scaleY);
    void LightenConfirmed(double lightenIntensity);
    void CannyConfirmed(double low, double high, int kernel);

private:
    Ui::FigureContainer *ui;
    cv::Mat* image;
    cv::Mat* displayedImage;

    int clickPosX, clickPosY;
    float zoom;
    bool isDragging;

};

#endif // FIGURECONTAINER_H