#include "Controller.h"
#include "CardView.h"
#include "CardContainer.h"
#include "HappyGroupWidget.h"
#include "MahjongJudgment.h"
#include <QApplication>

Controller::Controller(Player *p, QObject *parent) :
    QObject(parent),
    player(p),
    otherPlayersCard(nullptr),
    money(100)
{
    desk = new QWidget();
    mainLayout = new QHBoxLayout();
    desk->setLayout(mainLayout);

    leftLayout = new QHBoxLayout();
    mainLayout->addLayout(leftLayout, 6);
    leftLayout->addStretch(1);


    midLayout = new QVBoxLayout();
    mainLayout->addLayout(midLayout, 17);
    btnsLayout = new QHBoxLayout();
    cardsLayout = new QHBoxLayout();
    cardView = new CardView();
    cardView->initail(17);
    cardsLayout->addWidget(cardView);
    midLayout->addLayout(btnsLayout);
    midLayout->addLayout(cardsLayout);

    rightLayout = new QVBoxLayout();
    mainLayout->addLayout(rightLayout);

    QLabel* playerName = new QLabel(tr("Player: ") + player->getName());
    moneyLabel = new QLabel(tr("Money: ") + QString::number(money) + tr(" Yuan"));
    timeRecoder = new QLCDNumber();

    rightLayout->addWidget(playerName);
    rightLayout->addWidget(moneyLabel);
    rightLayout->addWidget(timeRecoder);
    connect(this, &Controller::asynHandleOperations, this, &Controller::onHandleOperations, Qt::QueuedConnection);
}

Controller::~Controller()
{

}

QWidget *Controller::widget()
{
    return desk;
}

CardView *Controller::getCardsView() const
{
    return cardView;
}

void Controller::onUpdateTime(unsigned sec)
{
    timeRecoder->display((int)sec);
}

void Controller::onMakeHappyGroup()
{
    QList<PlayerOperation> operations;
    operations.push_back(PO_MAKEGROUP);
    operations.push_back(PO_MAKEGROUPOK);
    handleOperations(operations);
}

void Controller::onUpdatedDrawedCard(PaperCard *card)
{
    otherPlayersCard = card;
}

void Controller::onHandleOperations()
{
    handleOperations();
}

void Controller::onBalance(int deltaMoney)
{
    money += deltaMoney;
    moneyLabel->setText(tr("Money: ") + QString::number(money) + tr(" Yuan"));
    clearLayout(leftLayout);
    emit updateDrawedArea(nullptr);
}

void Controller::handleOperations(QList<PlayerOperation> operations)
{
    playerOperations = operations;
    emit asynHandleOperations();
}

void Controller::clearLayout(QLayout *layout)
{
    QLayoutItem *item;
    while((item = layout->takeAt(0)) != 0){
        if(item->widget()){
            delete item->widget();
        }
        QLayout *childLayout = item->layout();
        if(childLayout){
            clearLayout(childLayout);
        }
        delete item;
    }
}

void Controller::moveToCardGroupArea(QList<PaperCard *> cards)
{
    HappyGroupWidget* hg = new HappyGroupWidget();
    hg->setCards(cards);
    leftLayout->addWidget(hg);
}
