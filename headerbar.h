
#ifndef HEADERBAR_H
#define HEADERBAR_H

#include <QWidget>
#include "./ui_headerbar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class HeaderBar; }
QT_END_NAMESPACE

class HeaderBar : public QWidget
{
    Q_OBJECT

public:
    HeaderBar(QWidget *parent = nullptr);
    ~HeaderBar();

private:
    Ui::HeaderBar *ui;
};

#endif // HEADERBAR_H
