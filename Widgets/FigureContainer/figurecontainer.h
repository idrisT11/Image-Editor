#ifndef FIGURECONTAINER_H
#define FIGURECONTAINER_H

#include <QWidget>
#include <QMouseEvent>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "Classes/HistoryManager/HistoryManager.h"

namespace Ui {
class FigureContainer;
}

enum InteractionType { DRAG, DRAW };


class FigureContainer : public QWidget
{
    Q_OBJECT

public:
    explicit FigureContainer(QWidget *parent = nullptr);
    ~FigureContainer();
    cv::Mat getCurrentImage();

private slots:
    void LoadNewImage(std::string str);

    void Mouse_current_pos();
    void Mouse_left_click();
    void Mouse_left_up();

    void ResizeConfirmed(double scaleX, double scaleY);
    void LightenConfirmed(double lightenIntensity);
    void CannyConfirmed(double low, double high, int kernel);
    void ErodeConfirmed(int kernelType, int kernelSize);
    void DilateConfirmed(int kernelType, int kernelSize);
    void FilterConfirmed(int filterType);
    void DetectFaceConfirmed();
    void PanoramaConfirmed();

    void SetInteractionType(InteractionType newInteractionType);
    void SetPickedColor(cv::Scalar newColor);
    void UndoAction();
    void RedoAction();

private:
    Ui::FigureContainer *ui;
    cv::Mat* image;
    cv::Mat* displayedImage;

    HistoryManager historyManager;

    InteractionType currentInteraction;
    cv::Scalar currentPickedColor;
    int clickPosX, clickPosY;
    bool isDragging;
};

#endif // FIGURECONTAINER_H
