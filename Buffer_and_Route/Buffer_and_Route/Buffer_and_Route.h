#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Buffer_and_Route.h"

class Buffer_and_Route : public QMainWindow
{
    Q_OBJECT

public:
    Buffer_and_Route(QWidget *parent = nullptr);
    ~Buffer_and_Route();

private:
    Ui::Buffer_and_RouteClass ui;
};
