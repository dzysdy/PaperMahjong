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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *mainLayout;
    QVBoxLayout *upLayout;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *drawedCardArea;
    QPushButton *startBtn;
    QVBoxLayout *downLayout;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QStringLiteral("background-color: rgb(30, 91, 76);"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        mainLayout = new QVBoxLayout();
        mainLayout->setSpacing(6);
        mainLayout->setObjectName(QStringLiteral("mainLayout"));
        upLayout = new QVBoxLayout();
        upLayout->setSpacing(6);
        upLayout->setObjectName(QStringLiteral("upLayout"));

        mainLayout->addLayout(upLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        drawedCardArea = new QHBoxLayout();
        drawedCardArea->setSpacing(6);
        drawedCardArea->setObjectName(QStringLiteral("drawedCardArea"));

        horizontalLayout->addLayout(drawedCardArea);

        startBtn = new QPushButton(centralWidget);
        startBtn->setObjectName(QStringLiteral("startBtn"));
        startBtn->setMinimumSize(QSize(0, 45));
        startBtn->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(startBtn);


        mainLayout->addLayout(horizontalLayout);

        downLayout = new QVBoxLayout();
        downLayout->setSpacing(6);
        downLayout->setObjectName(QStringLiteral("downLayout"));

        mainLayout->addLayout(downLayout);

        mainLayout->setStretch(0, 1);
        mainLayout->setStretch(1, 1);
        mainLayout->setStretch(2, 1);

        verticalLayout->addLayout(mainLayout);

        MainWindow->setCentralWidget(centralWidget);

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
