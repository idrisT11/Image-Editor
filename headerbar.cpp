
#include "headerbar.h"
#include "./ui_headerbar.h"

HeaderBar::HeaderBar(QWidget *parent)
    : QWidget(parent), ui(new Ui::HeaderBar)
{
    ui->setupUi(this);
}

HeaderBar::~HeaderBar()
{
    delete ui;
}

