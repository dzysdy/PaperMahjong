/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLCDNumber *remaindTime;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QWidget *upWidget;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *drawedCardArea;
    QPushButton *startBtn;
    QWidget *downWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1200, 800);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        remaindTime = new QLCDNumber(centralWidget);
        remaindTime->setObjectName(QStringLiteral("remaindTime"));
        remaindTime->setGeometry(QRect(990, 330, 91, 71));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 1181, 771));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        upWidget = new QWidget(verticalLayoutWidget);
        upWidget->setObjectName(QStringLiteral("upWidget"));

        verticalLayout->addWidget(upWidget, 0, Qt::AlignTop);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        drawedCardArea = new QHBoxLayout();
        drawedCardArea->setSpacing(6);
        drawedCardArea->setObjectName(QStringLiteral("drawedCardArea"));

        horizontalLayout->addLayout(drawedCardArea);

        startBtn = new QPushButton(verticalLayoutWidget);
        startBtn->setObjectName(QStringLiteral("startBtn"));

        horizontalLayout->addWidget(startBtn);


        verticalLayout->addLayout(horizontalLayout);

        downWidget = new QWidget(verticalLayoutWidget);
        downWidget->setObjectName(QStringLiteral("downWidget"));

        verticalLayout->addWidget(downWidget);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        startBtn->setText(QApplication::translate("MainWindow", "\346\226\260\347\232\204\344\270\200\345\261\200", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
