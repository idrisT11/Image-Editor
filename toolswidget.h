#ifndef TOOLSWIDGET_H
#define TOOLSWIDGET_H

#include <QWidget>

namespace Ui {
class ToolsWidget;
}

class ToolsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ToolsWidget(QWidget *parent = nullptr);
    ~ToolsWidget();

private:
    Ui::ToolsWidget *ui;
};

#endif // TOOLSWIDGET_H
