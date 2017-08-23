#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "MahjongJudgment.h"
#include "PaperMahjong.h"
#include "PaperCard.h"
#include "Player.h"
#include "CardsWidget.h"
#include "CardContainer.h"
#include "HappyGroupWidget.h"
#include "Util.h"
#include <QPushButton>
#include <QMessageBox>
#include <QLayout>

const int BUTTON_NUM = 8;
const QString gButtons[BUTTON_NUM] = {
    "chi",
    "peng",
    "ding",
    "hu",
    "da",
    "mo",
    "liaoxi",
    "guoxi",
};

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
    initailButtons();
    connectSignals();
}

void MainWindow::initailButtons()
{
    for (int i = 0; i < BUTTON_NUM; i++) {
        QString name = gButtons[i];
        QPushButton* button = new QPushButton(name);
        ui->buttonLayout->addWidget(button);
        buttons.insert(name, button);
        button->hide();
        connect(button, &QPushButton::clicked, this, &MainWindow::onOperatBtnClicked);
    }
}

void MainWindow::connectSignals()
{
    connect(judgment, &MahjongJudgment::updateTime, this, &MainWindow::onUpdateTime);
    connect(judgment, &MahjongJudgment::makeHappyGroup, this, &MainWindow::onMakeHappyGroup);
    connect(judgment, &MahjongJudgment::firstStep, this, &MainWindow::onFirstStep);
    connect(judgment, &MahjongJudgment::secondStep, this, &MainWindow::onSecondStep);
}

void MainWindow::showButtons(QList<PlayerOperation> operations)
{
    hideAllButtons();
    for (PlayerOperation operation : operations) {
        QString name = gButtons[operation - 1];
        buttons[name]->show();
    }
}

void MainWindow::hideAllButtons()
{
    for (QPushButton* button : buttons) {
        button->hide();
    }
}

void MainWindow::updateDrawedArea(CardContainer *container)
{
    if (drawedCardContainer) {
        drawedCardContainer->setParent(nullptr);
        ui->drawedCardArea->removeWidget(drawedCardContainer);
        delete drawedCardContainer;
    }
    drawedCardContainer = container;
    ui->drawedCardArea->addWidget(drawedCardContainer);
}

void MainWindow::onUpdateTime(unsigned sec)
{
    ui->remaindTime->display((int)sec);
}

void MainWindow::onMakeHappyGroup()
{
    cardsWidget->setMode(CardsWidget::CSM_LIAOXI);
    hideAllButtons();
    buttons["liaoxi"]->show();
}

void MainWindow::onFirstStep(QList<PlayerOperation> operations)
{
    cardsWidget->setMode(CardsWidget::CSM_CHI);
    showButtons(operations);
}

void MainWindow::onSecondStep(QList<PlayerOperation> operations)
{
    cardsWidget->setMode(CardsWidget::CSM_CUSTOM);
    showButtons(operations);
}

void MainWindow::on_startBtn_clicked()
{
    drawedCardContainer = nullptr;
    judgment->start();
    cardsWidget = new CardsWidget(this);
    cardsWidget->initail(17);
    cardsWidget->addCard(player1->cards());
    ui->cardsLayout->addWidget(cardsWidget);
    ui->startBtn->hide();
}

void MainWindow::onOperatBtnClicked()
{
    QPushButton* button = static_cast<QPushButton*>(sender());
    QString name = button->text();
    if (name == "liaoxi") {
        if (player1->makeHappyGroup(cardsWidget->getSelectedCards())) {
            QList<CardContainer*> containers = cardsWidget->takeSelectedCards();
            HappyGroupWidget* hg = new HappyGroupWidget();
            hg->setCardContainers(containers);
            ui->player1XiLayout->addWidget(hg);
        }
    }
    else if (name == "mo") {
        player1->drawsCard();
    }
    else if (name == "da") {
        QList<PaperCard *> cards = cardsWidget->getSelectedCards();
        if (cards.size() == 1)
            if (player1->removeCard(cards.first())) {
                QList<CardContainer*> containers = cardsWidget->takeSelectedCards();
                updateDrawedArea(containers.first());
            }
        else {
            QMessageBox::information(NULL, "Warning", "Please select a card first.", QMessageBox::Ok, QMessageBox::Ok);
        }
    }
}
