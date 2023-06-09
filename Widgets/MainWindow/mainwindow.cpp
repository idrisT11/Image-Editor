
#include <QScreen>
#include <QRect>

#include <QLineEdit>
#include <QHBoxLayout>
#include <QMenu>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Gimsep");
    showMaximized();

    setWindowIcon(QIcon(":/images/ressources/vgath-logo.png"));


    //=======================================================================
    // TabBar Events --------------------------------------------------------
    //=======================================================================
    filePath = "";
    aboutDialog = new AboutDialog;
    helpDialog = new HelpDialog;

    connect(ui->actionNewFile, SIGNAL(triggered()), this, SLOT(NewFile()));
    connect(ui->actionOpenFile, SIGNAL(triggered()), this, SLOT(OpenFile()));
    connect(ui->actionClose_2, SIGNAL(triggered()), this, SLOT(QuitWindow()));
    connect(ui->actionSaveFile, SIGNAL(triggered()), this, SLOT(SaveFile()));
    connect(ui->actionSaveFileAs, SIGNAL(triggered()), this, SLOT(SaveAsFile()));

    connect(this, SIGNAL(Loaded_New_Image(std::string)), ui->mainFrame, SLOT(LoadNewImage(std::string)));
    connect(this, SIGNAL(Loaded_Blank_Image()), ui->mainFrame, SLOT(LoadBlankImage()));

    connect(ui->actionAbout_Us, SIGNAL(triggered()), this, SLOT(OpenAbout()));
    connect(ui->actionInterface, SIGNAL(triggered()), this, SLOT(OpenHelp()));

    //=======================================================================
    // Tools&Popup Events ---------------------------------------------------
    //=======================================================================
    connect(ui->toolsWidget->resizePopup, SIGNAL(Apply_Scale(double,double)), ui->mainFrame, SLOT(ResizeConfirmed(double,double)));
    connect(ui->toolsWidget->lightenPopup, SIGNAL(Apply_LightIntensity(double)), ui->mainFrame, SLOT(LightenConfirmed(double)));
    connect(ui->toolsWidget->cannyPopup, SIGNAL(Apply_Canny(double,double,int)), ui->mainFrame, SLOT(CannyConfirmed(double,double,int)));
    connect(ui->toolsWidget->erodePopup, SIGNAL(Apply_Erode(int,int)), ui->mainFrame, SLOT(ErodeConfirmed(int,int)));
    connect(ui->toolsWidget->erodePopup, SIGNAL(Apply_Dilate(int,int)), ui->mainFrame, SLOT(DilateConfirmed(int,int)));

    connect(ui->toolsWidget, SIGNAL(Apply_Filter(int)), ui->mainFrame, SLOT(FilterConfirmed(int)));
    connect(ui->toolsWidget, SIGNAL(Apply_Face_Recognition()), ui->mainFrame, SLOT(DetectFaceConfirmed()));
    connect(ui->toolsWidget, SIGNAL(Apply_Panorama()), ui->mainFrame, SLOT(PanoramaConfirmed()));

    //=======================================================================
    // Left Interface Events ------------------------------------------------
    //=======================================================================
    connect(ui->leftInterface, SIGNAL(Set_Interaction_Mode(InteractionType)), ui->mainFrame, SLOT(SetInteractionType(InteractionType)));
    connect(ui->leftInterface, SIGNAL(Set_Picked_Color(cv::Scalar)), ui->mainFrame, SLOT(SetPickedColor(cv::Scalar)));
    connect(ui->leftInterface, SIGNAL(Action_Redo()), ui->mainFrame, SLOT(RedoAction()));
    connect(ui->leftInterface, SIGNAL(Action_Undo()), ui->mainFrame, SLOT(UndoAction()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

//=======================================================================
// TabBar Interactions --------------------------------------------------
//=======================================================================

void MainWindow::NewFile()
{
    this->filePath = "";

    emit Loaded_Blank_Image();
}

void MainWindow::OpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open a file", "./");
    this->filePath = fileName;

    emit Loaded_New_Image(fileName.toLocal8Bit().constData());
}

void MainWindow::SaveFile()
{
    if(this->filePath.length() == 0)
    {
        SaveAsFile();
    }
    else
    {
        cv::Mat image = ui->mainFrame->getCurrentImage();

        // Create QImage with same dimensions as input Mat to save
        //===================================================================
        const uchar *qImageBuffer = (const uchar*)image.data;
        QImage img(qImageBuffer, image.cols, image.rows, image.step, QImage::Format_RGB888);
        img = img.rgbSwapped();

        bool saved = img.save(this->filePath);

        if(!saved)
        {
            std::cerr << "Error while saving the image" << std::endl;
            return;
        }
        else
        {
            std::cout << "Image saved" << std::endl;
        }
    }
}

void MainWindow::SaveAsFile()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Save file", "", "Images (*.png *.jpg)");
    this->filePath = filePath;

    SaveFile();
}

void MainWindow::QuitWindow()
{
    this->close();
}

void MainWindow::OpenAbout()
{
    aboutDialog->show();
    aboutDialog->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    aboutDialog->resize(400, 250);
}

void MainWindow::OpenHelp()
{
    helpDialog->show();
    helpDialog->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    helpDialog->resize(450, 490);

}
