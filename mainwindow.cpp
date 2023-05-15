
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

    LayerWidget *layerWidget = new LayerWidget(this);

    //HeaderBar *headerBar = new HeaderBar(this);

    FigureContainer *figureContainer = new FigureContainer();

    QHBoxLayout *hbox = new QHBoxLayout(this);
    hbox->addWidget(figureContainer);
    hbox->addWidget(layerWidget);

    QWidget *placeholderWidget = new QWidget;
    placeholderWidget->setLayout(hbox);
    setCentralWidget(placeholderWidget);

    //cv::Mat mat = cv::imread("./shinzo.jpg");

/*
    // Set the color table (used to translate colour indexes to qRgb values)
    QVector<QRgb> colorTable;
    for (int i=0; i<256; i++)
            colorTable.push_back(qRgb(i,i,i));

    // Copy input Mat
    const uchar *qImageBuffer = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
    QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
    img.setColorTable(colorTable);
*/
    /*
    const uchar *qImageBuffer = (const uchar*)mat.data;
    // Create QImage with same dimensions as input Mat
    QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
    img = img.rgbSwapped();

    QHBoxLayout *hbox = new QHBoxLayout(this);


    QLabel *myLabel = new QLabel("wesh", this);
    myLabel->setPixmap(QPixmap::fromImage(img));
    //myLabel->setPixmap(QPixmap(":/images/shinzo.jpg"));

    myLabel->move(600, 600);
    myLabel->setStyleSheet("color: blue");

    hbox->addWidget(myLabel);

    QWidget *placeholderWidget = new QWidget;
    placeholderWidget->setLayout(hbox);
    setCentralWidget(placeholderWidget);
*/
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



