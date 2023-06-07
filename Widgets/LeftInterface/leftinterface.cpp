#include "leftinterface.h"
#include "./ui_leftinterface.h"

LeftInterface::LeftInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LeftInterface)
{
    ui->setupUi(this);
}

LeftInterface::~LeftInterface()
{
    delete ui;
}

void LeftInterface::applyStyleOnButton(QWidget *button, QString style)
{
    //Not a good way to implement this functionality
    QString currentStyleSheet = button->styleSheet();
    QString newStyleSheet = currentStyleSheet + style;
    button->setStyleSheet(newStyleSheet);
}

void LeftInterface::on_cursorButton_clicked()
{
    emit Set_Interaction_Mode(DRAG);

    applyStyleOnButton(ui->penButton, "background-color: rgb(105, 105, 105);");
    applyStyleOnButton(ui->cursorButton, "background-color: rgb(0, 97, 230);");
}

void LeftInterface::on_penButton_clicked()
{
    emit Set_Interaction_Mode(DRAW);

    applyStyleOnButton(ui->cursorButton, "background-color: rgb(105, 105, 105);");
    applyStyleOnButton(ui->penButton, "background-color: rgb(0, 97, 230);");
}

// COLOR PICKER SLOTS : -----------------------------------------------
// -------------------------------------------------------------

void LeftInterface::on_redButton_clicked()
{
    cv::Scalar s = COLORMAP["RED"];

    emit Set_Picked_Color(s);
}

