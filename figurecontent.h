#ifndef FIGURECONTENT_H
#define FIGURECONTENT_H

#include <QLabel>
#include <QMouseEvent>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace Ui {
class FigureContent;
}

class FigureContent : public QLabel
{
    Q_OBJECT

public:
    explicit FigureContent(QWidget *parent = nullptr);
    ~FigureContent();
    void setupImage(cv::Mat* o_image = nullptr);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    int x, y;

private:
    Ui::FigureContent *ui;
    cv::Mat* image;

signals:
    void Mouse_Pos();
    void Mouse_Pressed();
    void Mouse_Released();

};

#endif // FIGURECONTENT_H
