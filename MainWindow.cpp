#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "MahjongJudgment.h"
#include "PaperMahjong.h"
#include "PaperCard.h"
#include "CardsWidget.h"
#include "CardContainer.h"
#include "HappyGroupWidget.h"
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
    player1 = new Player(mahjong);
    player2 = new Player(mahjong);
    judgment->addPlayer(player1);
    judgment->addPlayer(player2);
    player1->desk()->setParent(ui->upWidget);
    player2->desk()->setParent(ui->downWidget);
}

void MainWindow::on_startBtn_clicked()
{
    //drawedCardContainer = nullptr;
    //cardsWidget = new CardsWidget(this);
    judgment->start();
    //cardsWidget->initail(17);
    //cardsWidget->addCard(player1->cards());
    //ui->cardsLayout->addWidget(cardsWidget);
    ui->startBtn->hide();
}

