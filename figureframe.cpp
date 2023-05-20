#include "figureframe.h"
#include<iostream>
FigureFrame::FigureFrame(QWidget *parent) :
    QFrame(parent)
{

}

FigureFrame::~FigureFrame()
{
}

void FigureFrame::setup()
{
    this->setMouseTracking(true);
}


void FigureFrame::mouseMoveEvent(QMouseEvent *event)
{
    this->x = event->x();
    this->y = event->y();
    std::cout << this->x << " " << this->y << std::endl;
    emit Mouse_Pos_FigureFrame();
}
