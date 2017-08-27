#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "MahjongJudgment.h"
#include "PaperMahjong.h"
#include "PaperCard.h"
#include "CardView.h"
#include "CardContainer.h"
#include "HappyGroupWidget.h"
#include "Controller.h"
#include "Util.h"
#include <QPushButton>
#include <QMessageBox>
#include <QLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mahjong(nullptr),
    judgment(nullptr),
    player1(nullptr),
    player2(nullptr),
    drawedCardContainer(nullptr)
{
    ui->setupUi(this);
    initail();
}

MainWindow::~MainWindow()
{
    delete player2;
    delete player1;
    delete judgment;
    delete mahjong;
    delete ui;
}

void MainWindow::initail()
{
    mahjong = new PaperMahjong();
    judgment = new MahjongJudgment(mahjong);
    player1 = new Player(mahjong, judgment, 0);
    player2 = new Player(mahjong, judgment, 1);
    judgment->addPlayer(player1);
    judgment->addPlayer(player2);
    ui->downLayout->addWidget(player1->desk());
    ui->upLayout->addWidget(player2->desk());
    connect(player1->getController(), &Controller::updateDrawedArea, this, &MainWindow::onUpdateDrawedArea);
    connect(player2->getController(), &Controller::updateDrawedArea, this, &MainWindow::onUpdateDrawedArea);
    connect(this, &MainWindow::updateDrawedCard, player1->getController(), &Controller::onUpdatedDrawedCard);
    connect(this, &MainWindow::updateDrawedCard, player2->getController(), &Controller::onUpdatedDrawedCard);
}

void MainWindow::onUpdateDrawedArea(PaperCard *card)
{
    if (!drawedCardContainer) {
        drawedCardContainer = new QLabel();
        ui->drawedCardArea->addWidget(drawedCardContainer);
    }
    QImage image(Util::getResourcePath()+card->getName());
    drawedCardContainer->setPixmap(QPixmap::fromImage(image.scaledToHeight(200)));
    PaperCard* oldCard = static_cast<PaperCard*>(drawedCardContainer->userData(0));
    delete oldCard;
    if (card) {
        emit updateDrawedCard(card);
        drawedCardContainer->setUserData(0, card);
        drawedCardContainer->update();
    }
}

void MainWindow::on_startBtn_clicked()
{
    drawedCardContainer = nullptr;
    judgment->start();
    ui->startBtn->hide();
}

