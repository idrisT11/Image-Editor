#ifndef FIGUREFRAME_H
#define FIGUREFRAME_H

#include <QFrame>
#include <QMouseEvent>

namespace Ui {
class FigureFrame;
}

class FigureFrame : public QFrame
{
    Q_OBJECT

public:
    explicit FigureFrame(QWidget *parent = nullptr);
    ~FigureFrame();
    void setup();
    void mouseMoveEvent(QMouseEvent *event);
    //void wheelEvent(QWheelEvent *event);

    int x, y;
    int zoom;

signals:
    void Mouse_Pos_FigureFrame();

};

#endif // FIGUREFRAME_H
