
#include <QLabel>
#include <QFileDialog>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/stitching.hpp>

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
    image = new cv::Mat(this->height()-500, this->width()-500, CV_8UC3, cv::Scalar(255, 255, 255));

    //*image = cv::imread("./shinzo.jpg");
    ui->myLabel->setupImage(image);

    std::cout << ui->figureFrame->width() << "??" << this->width() << "--" <<  ui->figureFrame->geometry().width() << std::endl;
    std::cout << ui->figureFrame->height() << "??" << this->height() << "--" <<  ui->figureFrame->geometry().height() << std::endl;

    //ui->myLabel->move((this->width() - ui->myLabel->width()-100)/2,
    //                  (this->height() - ui->myLabel->height()-00)/2);

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

//=======================================================================
// File Management ------------------------------------------------------
//=======================================================================

cv::Mat FigureContainer::getCurrentImage()
{
    return *image;
}

void FigureContainer::LoadNewImage(std::string src)
{
    cv::Mat newImage = cv::imread(src);
    if(newImage.empty())
    {
        return;
    }
    *image = newImage;
    ui->myLabel->setupImage(image);
}

void FigureContainer::LoadBlankImage()
{
    *image = cv::Mat(500, this->width()-500, CV_8UC3, cv::Scalar(255, 255, 255));

    ui->myLabel->setupImage(image);
}

//=======================================================================
// Mouse Interactions ---------------------------------------------------
//=======================================================================

void FigureContainer::Mouse_current_pos()
{

    if (this->currentInteraction == DRAG && this->isDragging)
    {
        ui->myLabel->move(
            ui->figureFrame->x - this->clickPosX,
            ui->figureFrame->y - this->clickPosY
        );
    }

    else if (this->currentInteraction == DRAW && this->isDragging)
    {
        double pointX = ui->myLabel->x,
               pointY = ui->myLabel->y;

        *image = ImageTransformer::drawPoint(*image, cv::Point(pointX, pointY), currentPickedColor, 3);

        ui->myLabel->setupImage(image);
    }
}

void FigureContainer::Mouse_left_click()
{
    if(currentInteraction == DRAW)
    {
        cv::Mat tmp;              //We have to create a copy here because it looks like *image can be modified by
        image->copyTo(tmp);       //the event of the slot Mouse_current_pos

        historyManager.pushAction(tmp);
    }

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

    ui->myLabel->setupImage(image);
}

void FigureContainer::DetectFaceConfirmed()
{
    historyManager.pushAction(*image);

    Ptr<LBPHFaceRecognizer> recognizer = LBPHFaceRecognizer::create();
    std::string cascadePath = "./faceDetection/haarcascades/haarcascade_frontalface_alt.xml";

    CascadeClassifier cascade;
    if (!cascade.load(cascadePath))
    {
        std::cerr << "Failed to load cascade classifier." << std::endl;
        return;
    }
    recognizer->read("./faceDetection/recognizer/trained_recognizer.yml");
//C:/Users/knob/Documents/GitHub/Image-Editor/Image-Editor/ressources

    *image = ImageTransformer::detectAndRecognizeFaces(*image, cascade, recognizer, 1.1);

    ui->myLabel->setupImage(image);
}

void FigureContainer::PanoramaConfirmed()
{
    historyManager.pushAction(*image);

    std::vector<cv::Mat> imagesToProcess = {};

    QStringList fileNames = QFileDialog::getOpenFileNames(this, "Open a file", "./", tr("Images(*.png *.jpg"));
    for (int i = 0; i < fileNames.size(); ++i)
    {
        std::string fileName = fileNames.at(i).toLocal8Bit().constData();

        cv::Mat img = cv::imread(fileName);
        if (img.empty())
        {
            std::cout<< " - Cannot read image"<<std::endl;
            return;
        }

        imagesToProcess.push_back(img);
    }

    imagesToProcess.push_back(*image);

    *image = ImageTransformer::panorama(imagesToProcess);

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
    *image = historyManager.redoAction(*image);

    ui->myLabel->setupImage(image);
}

