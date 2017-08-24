#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "MahjongJudgment.h"
#include "PaperMahjong.h"
#include "PaperCard.h"
#include "CardsWidget.h"
#include "CardContainer.h"
#include "HappyGroupWidget.h"
#include "Controller.h"
#include "Util.h"
#include <QPushButton>
#include <QMessageBox>
#include <QLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initail();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initail()
{
    mahjong = new PaperMahjong();
    judgment = new MahjongJudgment(mahjong);
    player1 = new Player(mahjong, judgment);
    player2 = new Player(mahjong, judgment);
    judgment->addPlayer(player1);
    judgment->addPlayer(player2);
    ui->downLayout->addWidget(player1->desk());
    ui->upLayout->addWidget(player2->desk());
    connect(player1->getController(), &Controller::updateDrawedArea, this, &MainWindow::onUpdateDrawedArea);
    connect(player2->getController(), &Controller::updateDrawedArea, this, &MainWindow::onUpdateDrawedArea);
}

void MainWindow::onUpdateDrawedArea(CardContainer *container)
{
    if (drawedCardContainer) {
        drawedCardContainer->setParent(nullptr);
        ui->drawedCardArea->removeWidget(drawedCardContainer);
        delete drawedCardContainer;
    }
    drawedCardContainer = container;
    ui->drawedCardArea->addWidget(drawedCardContainer);
}

void MainWindow::on_startBtn_clicked()
{
    drawedCardContainer = nullptr;
    judgment->start();
    ui->startBtn->hide();
}

