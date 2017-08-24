#-------------------------------------------------
#
# Project created by QtCreator 2017-08-19T22:24:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PaperMahjong
TEMPLATE = app
MOC_DIR = ./moc
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        MainWindow.cpp \
    PaperMahjong.cpp \
    PaperCard.cpp \
    Player.cpp \
    MahjongJudgment.cpp \
    Util.cpp \
    CardContainer.cpp \
    CardsWidget.cpp \
    HappyGroupWidget.cpp \
    MajhongAlgorithm.cpp \
    MajhongAlgorithmWraper.cpp \
    HappyGroupHelper.cpp \
    WorkDesk.cpp \
    Controller.cpp \
    AIController.cpp

HEADERS  += MainWindow.h \
    PaperMahjong.h \
    PaperCard.h \
    Player.h \
    MahjongJudgment.h \
    Util.h \
    CardContainer.h \
    CardsWidget.h \
    HappyGroupWidget.h \
    MajhongAlgorithm.h \
    MajhongAlgorithmWraper.h \
    HappyGroupHelper.h \
    WorkDesk.h \
    Controller.h \
    AIController.h

FORMS    += mainwindow.ui
