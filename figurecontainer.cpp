
#include <QLabel>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Classes/ImageTransformer/ImageTransformer.h"
#include "figurecontainer.h"
#include "figurecontent.h"
#include "figureframe.h"

#include "ui_figurecontainer.h"

FigureContainer::FigureContainer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FigureContainer)
{
    ui->setupUi(this);

    //Temporary: init image
    image = new cv::Mat();
    *image = cv::imread("./shinzo.jpg");
    ui->myLabel->setupImage(image);

    ui->myLabel->move((ui->figureFrame->width() - ui->myLabel->width())/2,
                      (ui->figureFrame->height() - ui->myLabel->height())/2);

    ui->figureFrame->setup();

    connect(ui->myLabel,        SIGNAL(Mouse_Pos()), this, SLOT(Mouse_current_pos()));
    connect(ui->figureFrame,    SIGNAL(Mouse_Pos_FigureFrame()), this, SLOT(Mouse_current_pos()));

    connect(ui->myLabel, SIGNAL(Mouse_Pressed()), this, SLOT(Mouse_left_click()));
    connect(ui->myLabel, SIGNAL(Mouse_Released()), this, SLOT(Mouse_left_up()));


    isDragging = false;
}

FigureContainer::~FigureContainer()
{
    delete ui;
}

void FigureContainer::Mouse_current_pos()
{
    ui->pushButton->setText(QString("X = %1 & Y = %2").arg(ui->figureFrame->x).arg(ui->figureFrame->y));

    if (this->isDragging)
    {
        ui->myLabel->move(
            ui->figureFrame->x - this->clickPosX,
            ui->figureFrame->y - this->clickPosY
          );
    }
}

void FigureContainer::Mouse_left_click()
{
    this->isDragging = true;
    this->clickPosX = ui->myLabel->x;//this value is relative to the figurecontent
    this->clickPosY = ui->myLabel->y;
}

void FigureContainer::Mouse_left_up()
{
    this->isDragging = false;
}

//=======================================================================
// Popups interface ----------------------------------------------------
//=======================================================================

void FigureContainer::ResizeConfirmed(double scaleX, double scaleY)
{
    *image = ImageTransformer::resize(*image, scaleX, scaleY);

    ui->myLabel->setupImage(image);
    ui->myLabel->move((ui->figureFrame->width() - ui->myLabel->width())/2,
                      (ui->figureFrame->height() - ui->myLabel->height())/2);
}


void FigureContainer::LightenConfirmed(double lightenIntensity)
{
    *image = ImageTransformer::LightenDarken(*image, lightenIntensity);

    ui->myLabel->setupImage(image);
}

void FigureContainer::CannyConfirmed(double low, double high, int kernel)
{
    ui->pushButton->setText(QString("zeybb L = %1").arg(low));

    *image = ImageTransformer::canny(*image, low, high, kernel);

    ui->myLabel->setupImage(image);
}

void FigureContainer::ErodeConfirmed(int kernelType, int kernelSize)
{
    *image = ImageTransformer::erosion(*image, kernelSize, kernelType);

    ui->myLabel->setupImage(image);
}

void FigureContainer::DilateConfirmed(int kernelType, int kernelSize)
{
    *image = ImageTransformer::dilatation(*image, kernelSize, kernelType);

    ui->myLabel->setupImage(image);
}

void FigureContainer::FilterConfirmed(int filterType)
{
    *image = ImageTransformer::applyFilter(*image, filterType);
    std::cout << image->cols << "  " << image->rows << std::endl;

    ui->myLabel->setupImage(image);
}
