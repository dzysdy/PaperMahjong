#include "Controller.h"
#include "CardView.h"
#include "CardContainer.h"
#include "HappyGroupWidget.h"
#include "MahjongJudgment.h"

Controller::Controller(Player *p, QObject *parent) :
    QObject(parent),
    player(p),
    otherPlayersCard(nullptr)
{
    desk = new QWidget();
    mainLayout = new QHBoxLayout();
    desk->setLayout(mainLayout);

    leftLayout = new QHBoxLayout();
    mainLayout->addLayout(leftLayout, 6);


    midLayout = new QVBoxLayout();
    mainLayout->addLayout(midLayout, 17);
    btnsLayout = new QHBoxLayout();
    cardsLayout = new QHBoxLayout();
    cardView = new CardView();
    cardView->initail(17);
    cardView->setMinimumWidth(400);
    cardsLayout->addWidget(cardView);
    cardsLayout->addStretch(1);
    midLayout->addLayout(btnsLayout);
    midLayout->addLayout(cardsLayout);

    rightLayout = new QVBoxLayout();
    mainLayout->addLayout(rightLayout);

    QLabel* playerName = new QLabel("Player: " + player->getName());
    timeRecoder = new QLCDNumber();
    rightLayout->addWidget(playerName);
    rightLayout->addWidget(timeRecoder);
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

void Controller::connectSignals(MahjongJudgment* judgment)
{
    connect(judgment, &MahjongJudgment::makeHappyGroup, this, &Controller::onMakeHappyGroup);
//    connect(judgment, &MahjongJudgment::updateTime, this, &Controller::onUpdateTime);
//    connect(judgment, &MahjongJudgment::firstStep, this, &Controller::onFirstStep);
//    connect(judgment, &MahjongJudgment::secondStep, this, &Controller::onSecondStep);
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

void Controller::moveToCardGroupArea(QList<PaperCard *> cards)
{
    HappyGroupWidget* hg = new HappyGroupWidget();
    hg->setCards(cards);
    leftLayout->addWidget(hg);
}

void Controller::setMyTurn(bool b)
{
    isMyTurn = b;
}
