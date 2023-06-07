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
    emit Set_Picked_Color(COLORMAP["RED"]);
}

void LeftInterface::on_orangeButton_clicked()
{
    emit Set_Picked_Color(COLORMAP["ORANGE"]);
}

void LeftInterface::on_yellowButton_clicked()
{
    emit Set_Picked_Color(COLORMAP["YELLOW"]);
}

void LeftInterface::on_greenButton_clicked()
{
    emit Set_Picked_Color(COLORMAP["GREEN"]);
}

void LeftInterface::on_cyanButton_clicked()
{
    emit Set_Picked_Color(COLORMAP["CYAN"]);
}

void LeftInterface::on_blueButton_clicked()
{
    emit Set_Picked_Color(COLORMAP["BLUE"]);
}

void LeftInterface::on_purpleButton_clicked()
{
    emit Set_Picked_Color(COLORMAP["PURPLE"]);
}

void LeftInterface::on_violetButton_clicked()
{
    emit Set_Picked_Color(COLORMAP["VIOLET"]);
}

void LeftInterface::on_pinkButton_clicked()
{
    emit Set_Picked_Color(COLORMAP["PINK"]);
}

void LeftInterface::on_whiteButton_clicked()
{
    emit Set_Picked_Color(COLORMAP["WHITE"]);
}

void LeftInterface::on_greyButton_clicked()
{
    emit Set_Picked_Color(COLORMAP["GREY"]);
}

void LeftInterface::on_blackButton_clicked()
{
    emit Set_Picked_Color(COLORMAP["BLACK"]);
}

// ACTION HISTORY SLOTS : --------------------------------------
// -------------------------------------------------------------
void LeftInterface::on_redoButton_clicked()
{
    emit Action_Redo();
}

void LeftInterface::on_undoButton_clicked()
{
    emit Action_Undo();
}

