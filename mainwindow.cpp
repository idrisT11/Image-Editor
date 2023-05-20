
#include <QScreen>
#include <QRect>

#include <QLineEdit>
#include <QHBoxLayout>
#include <QMenu>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "layerwidget.h"
#include "figurecontainer.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Gimsep");
    showMaximized();

    setWindowIcon(QIcon(":/images/vgath-logo.png"));

    // Event: When user click on apply resize
    connect(ui->widget_4->resizePopup, SIGNAL(Apply_Scale(double, double)), ui->MainFrame, SLOT(ResizeConfirmed(double, double)));
    connect(ui->widget_4->lightenPopup, SIGNAL(Apply_LightIntensity(double)), ui->MainFrame, SLOT(LightenConfirmed(double)));


}

MainWindow::~MainWindow()
{
    delete ui;
}
