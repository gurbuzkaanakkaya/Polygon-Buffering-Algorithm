/********************************************************************************
** Form generated from reading UI file 'Buffer_and_Route.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUFFER_AND_ROUTE_H
#define UI_BUFFER_AND_ROUTE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Buffer_and_RouteClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Buffer_and_RouteClass)
    {
        if (Buffer_and_RouteClass->objectName().isEmpty())
            Buffer_and_RouteClass->setObjectName("Buffer_and_RouteClass");
        Buffer_and_RouteClass->resize(600, 400);
        menuBar = new QMenuBar(Buffer_and_RouteClass);
        menuBar->setObjectName("menuBar");
        Buffer_and_RouteClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Buffer_and_RouteClass);
        mainToolBar->setObjectName("mainToolBar");
        Buffer_and_RouteClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Buffer_and_RouteClass);
        centralWidget->setObjectName("centralWidget");
        Buffer_and_RouteClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Buffer_and_RouteClass);
        statusBar->setObjectName("statusBar");
        Buffer_and_RouteClass->setStatusBar(statusBar);

        retranslateUi(Buffer_and_RouteClass);

        QMetaObject::connectSlotsByName(Buffer_and_RouteClass);
    } // setupUi

    void retranslateUi(QMainWindow *Buffer_and_RouteClass)
    {
        Buffer_and_RouteClass->setWindowTitle(QCoreApplication::translate("Buffer_and_RouteClass", "Buffer_and_Route", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Buffer_and_RouteClass: public Ui_Buffer_and_RouteClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUFFER_AND_ROUTE_H
