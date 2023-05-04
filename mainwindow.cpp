
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QMenu>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "headerbar.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("MyWindow");
    resize(500, 600);

    HeaderBar *headerBar = new HeaderBar(this);


    /*QHBoxLayout *hbox = new QHBoxLayout(this);
    //hbox->addWidget(headerBar);

    QWidget *placeholderWidget = new QWidget;
    placeholderWidget->setLayout(hbox);
    setCentralWidget(placeholderWidget);*/

/*
    QLabel *label = new QLabel("This is a test", this);
    label->setText("Wesh sahbi");
    label->move(100, 200);
    label->setFont(QFont("Times", 15));
    label->setStyleSheet("color: blue");
    label->setGeometry(100,100, 30,300);

    label->setPixmap(QPixmap(":/images/shinzo.jpg"));

    QPushButton *btn = new QPushButton("Click", this);
    btn->setIcon(QIcon(":/images/shinzo.jpg"));

    /*QMenu *menu = new QMenu();
    menu->addAction("Past");
    menu->addAction("Copy");
    menu->addAction("Cut");

    btn->setMenu(menu);
    connect(btn, SIGNAL(clicked()), this, SLOT(ChangeText()));

    lbl = new QLabel("wesh", this);

    QHBoxLayout *hbox = new QHBoxLayout(this);
    hbox->addWidget(btn);
    hbox->addWidget(lbl);
    QWidget *placeholderWidget = new QWidget;
    placeholderWidget->setLayout(hbox);
    setCentralWidget(placeholderWidget);

*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ChangeText()
{
    lbl->setText("Changed !");
}


/*QPushButton *btn2 = new QPushButton("Click2", this);
    btn->setIcon(QIcon(":/images/shinzo.jpg"));

    QPushButton *btn3 = new QPushButton("Click3", this);
    btn->setIcon(QIcon(":/images/shinzo.jpg"));

    QHBoxLayout *hbox = new QHBoxLayout(this);
    hbox->addWidget(btn);
    hbox->addWidget(btn2);
    hbox->addWidget(btn3);

    QWidget *placeholderWidget = new QWidget;
    placeholderWidget->setLayout(hbox);
    setCentralWidget(placeholderWidget);

    QLineEdit *edit = new QLineEdit(this);
    edit->setEchoMode(QLineEdit::EchoMode::Password);*/



