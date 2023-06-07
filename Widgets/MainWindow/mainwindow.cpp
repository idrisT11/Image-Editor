
#include <QScreen>
#include <QRect>

#include <QLineEdit>
#include <QHBoxLayout>
#include <QMenu>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "Widgets/LayerWidget/layerwidget.h"
#include "Widgets/FigureContainer/figurecontainer.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Gimsep");
    showMaximized();

    setWindowIcon(QIcon(":/images/ressources/vgath-logo.png"));


    connect(ui->actionOpenFile, SIGNAL(triggered()), this, SLOT(OpenFile()));


    // Event: When user click on apply resize
    connect(ui->widget_4->resizePopup, SIGNAL(Apply_Scale(double,double)), ui->mainFrame, SLOT(ResizeConfirmed(double,double)));
    connect(ui->widget_4->lightenPopup, SIGNAL(Apply_LightIntensity(double)), ui->mainFrame, SLOT(LightenConfirmed(double)));
    connect(ui->widget_4->cannyPopup, SIGNAL(Apply_Canny(double,double,int)), ui->mainFrame, SLOT(CannyConfirmed(double,double,int)));
    connect(ui->widget_4->erodePopup, SIGNAL(Apply_Erode(int,int)), ui->mainFrame, SLOT(ErodeConfirmed(int,int)));
    connect(ui->widget_4->erodePopup, SIGNAL(Apply_Dilate(int,int)), ui->mainFrame, SLOT(DilateConfirmed(int,int)));

    connect(ui->widget_4, SIGNAL(Apply_Filter(int)), ui->mainFrame, SLOT(FilterConfirmed(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open a file", "./");
    //std::cout << fileName;

}
