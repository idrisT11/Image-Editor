
#include <QLabel>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "figurecontainer.h"
#include "figurecontent.h"
#include "figureframe.h"

#include "ui_figurecontainer.h"

FigureContainer::FigureContainer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FigureContainer)
{
    ui->setupUi(this);
    image = new cv::Mat();
    ui->myLabel->setup();
    ui->myLabel->move(0, 0);

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
        ui->myLabel->move(ui->figureFrame->x - this->clickPosX,
            ui->figureFrame->y - this->clickPosY);
    }
}

void FigureContainer::Mouse_left_click()
{
    this->isDragging = true;
}

void FigureContainer::Mouse_left_up()
{
    this->isDragging = false;
    this->clickPosX = - ui->myLabel->x + ui->figureFrame->x; //this value is relative to the figurecontent
    this->clickPosY = - ui->myLabel->y + ui->figureFrame->y;
}

