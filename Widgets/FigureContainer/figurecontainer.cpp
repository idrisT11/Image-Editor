
#include <QLabel>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Classes/ImageTransformer/ImageTransformer.h"
#include "Widgets/FigureContainer/figurecontainer.h"
#include "Widgets/FigureContent/figurecontent.h"
#include "Widgets/FigureFrame/figureframe.h"

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
    currentInteraction = DRAG;
    currentPickedColor = cv::Scalar(0, 0, 255);
}

FigureContainer::~FigureContainer()
{
    delete ui;
}

void FigureContainer::Mouse_current_pos()
{
    ui->pushButton->setText(QString("X = %1 & Y = %2").arg(ui->figureFrame->x).arg(ui->figureFrame->y));

    if (this->currentInteraction == DRAG && this->isDragging)
    {
        ui->myLabel->move(
            ui->figureFrame->x - this->clickPosX,
            ui->figureFrame->y - this->clickPosY
        );
    }

    else if (this->currentInteraction == DRAW &&  this->isDragging)
    {
        double pointX = ui->myLabel->x,
               pointY = ui->myLabel->y;

        *image = ImageTransformer::drawPoint(*image, cv::Point(pointX, pointY), currentPickedColor, 3);

        ui->myLabel->setupImage(image);
    }
}

void FigureContainer::Mouse_left_click()
{
    this->isDragging = true;
    this->clickPosX = ui->myLabel->x;//this value is relative to the figurecontent
    this->clickPosY = ui->myLabel->y;

    if(currentInteraction == DRAW)
    {
        historyManager.pushAction(*image);
    }
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
    historyManager.pushAction(*image);

    *image = ImageTransformer::resize(*image, scaleX, scaleY);

    ui->myLabel->setupImage(image);
    ui->myLabel->move((ui->figureFrame->width() - ui->myLabel->width())/2,
                      (ui->figureFrame->height() - ui->myLabel->height())/2);
}


void FigureContainer::LightenConfirmed(double lightenIntensity)
{
    historyManager.pushAction(*image);

    *image = ImageTransformer::LightenDarken(*image, lightenIntensity);

    ui->myLabel->setupImage(image);
}

void FigureContainer::CannyConfirmed(double low, double high, int kernel)
{
    historyManager.pushAction(*image);

    *image = ImageTransformer::canny(*image, low, high, kernel);

    ui->myLabel->setupImage(image);
}

void FigureContainer::ErodeConfirmed(int kernelType, int kernelSize)
{
    historyManager.pushAction(*image);

    *image = ImageTransformer::erosion(*image, kernelSize, kernelType);

    ui->myLabel->setupImage(image);
}

void FigureContainer::DilateConfirmed(int kernelType, int kernelSize)
{
    historyManager.pushAction(*image);

    *image = ImageTransformer::dilatation(*image, kernelSize, kernelType);

    ui->myLabel->setupImage(image);
}

void FigureContainer::FilterConfirmed(int filterType)
{
    historyManager.pushAction(*image);

    *image = ImageTransformer::applyFilter(*image, filterType);
    std::cout << image->cols << "  " << image->rows << std::endl;

    ui->myLabel->setupImage(image);
}

//=======================================================================
// Interactions interface slots -----------------------------------------
//=======================================================================

void FigureContainer::SetInteractionType(InteractionType newInteractionType)
{
    currentInteraction = newInteractionType;
}

void FigureContainer::SetPickedColor(cv::Scalar newColor)
{
    currentPickedColor = newColor;
}

//=======================================================================
// Action History Slots -------------------------------------------------
//=======================================================================
void FigureContainer::UndoAction()
{
    *image = historyManager.undoAction(*image);

    ui->myLabel->setupImage(image);
}

void FigureContainer::RedoAction()
{
    *image = historyManager.undoAction(*image);
}

