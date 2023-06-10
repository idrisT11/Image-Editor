#include "figurecontent.h"

FigureContent::FigureContent(QWidget *parent) :
    QLabel(parent)
{
    image = new cv::Mat();

    //this->setPixmap(QPixmap::fromImage(img));
    //this->setPixmap(QPixmap(":/images/shinzo.jpg"));

    this->setMouseTracking(true);
}

FigureContent::~FigureContent()
{
}

void FigureContent::setupImage(cv::Mat* o_image)
{
    if (o_image != nullptr)
    {
        image = o_image;
    }

    const uchar *qImageBuffer = (const uchar*)image->data;
    // Create QImage with same dimensions as input Mat
    QImage img(qImageBuffer, image->cols, image->rows, image->step, QImage::Format_RGB888);
    img = img.rgbSwapped();

    this->setPixmap(QPixmap::fromImage(img));
    this->setScaledContents(false);
    this->setFixedSize(img.width(),img.height());
}

void FigureContent::mouseMoveEvent(QMouseEvent *event)
{
    this->x = event->x();
    this->y = event->y();

    emit Mouse_Pos();

    event->ignore();
}

void FigureContent::mousePressEvent(QMouseEvent *event)
{
    //this->x = event->x();
    //this->y = event->y();

    if (event->button() == Qt::LeftButton)
        //&& this->geometry().contains(event->pos()))
    {
        emit Mouse_Pressed();
    }
}

void FigureContent::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        //&& this->geometry().contains(event->pos()))
    {
        emit Mouse_Released();
    }
}
