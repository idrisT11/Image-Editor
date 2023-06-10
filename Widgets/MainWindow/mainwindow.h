
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include<QLabel>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLabel *lbl;
    QString filePath;

public slots:
    void NewFile();
    void OpenFile();
    void SaveFile();
    void SaveAsFile();
    void QuitWindow();

signals:
    void Loaded_New_Image(std::string);
    void Loaded_Blank_Image();

};

#endif // MAINWINDOW_H
