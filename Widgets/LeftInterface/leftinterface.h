#ifndef LEFTINTERFACE_H
#define LEFTINTERFACE_H

#include <QWidget>
#include "./ui_leftinterface.h"

namespace Ui {
class LeftInterface;
}

class LeftInterface : public QWidget
{
    Q_OBJECT

public:
    explicit LeftInterface(QWidget *parent = nullptr);
    ~LeftInterface();

private:
    Ui::LeftInterface *ui;
};

#endif // LEFTINTERFACE_H
