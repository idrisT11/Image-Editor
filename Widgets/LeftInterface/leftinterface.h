#ifndef LEFTINTERFACE_H
#define LEFTINTERFACE_H

#include <QWidget>
#include "Widgets/FigureContainer/figurecontainer.h"
#include "./ui_leftinterface.h"

namespace Ui {
class LeftInterface;
}

class LeftInterface : public QWidget
{
    Q_OBJECT

public:
    explicit LeftInterface(QWidget *parent = nullptr);
    ~LeftInterface();

    std::map<std::string, cv::Scalar> COLORMAP = {
        {"RED", cv::Scalar(0, 0, 255)},
        {"ORANGE", cv::Scalar(0, 165, 255)},
        {"YELLOW", cv::Scalar(0, 255, 255)},
        {"GREEN", cv::Scalar(0, 255, 0)},
        {"CYAN", cv::Scalar(255, 255, 0)},
        {"BLUE", cv::Scalar(255, 0, 0)},
        {"PURPLE", cv::Scalar(255, 0, 255)},
        {"VOILET", cv::Scalar(238, 130, 238)},
        {"PINK", cv::Scalar(255, 192, 203)},
        {"WHITE", cv::Scalar(255, 255, 255)},
        {"GREY", cv::Scalar(165, 165, 165)},
        {"BLACK", cv::Scalar(0, 0, 0)},
    };

private slots:
    void on_cursorButton_clicked();
    void on_penButton_clicked();

    void on_redButton_clicked();

private:
    Ui::LeftInterface *ui;
    void applyStyleOnButton(QWidget *button, QString style);

signals:
    void Set_Interaction_Mode(InteractionType);
    void Set_Picked_Color(cv::Scalar);
};

#endif // LEFTINTERFACE_H
