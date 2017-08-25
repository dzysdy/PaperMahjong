#include "Controller.h"
#include "CardsWidget.h"
#include "CardContainer.h"
#include "HappyGroupWidget.h"
#include "MahjongJudgment.h"

Controller::Controller(Player *p, QObject *parent) :
    QObject(parent),
    player(p),
    otherPlayersCard(nullptr)
{
    desk = new QWidget();
//    QPalette pal;
//    pal.setColor(QPalette::Background, Qt::green);
//    desk->setAutoFillBackground(true);
//    desk->setPalette(pal);
    mainLayout = new QHBoxLayout();
    desk->setLayout(mainLayout);

    leftLayout = new QHBoxLayout();
    mainLayout->addLayout(leftLayout, 6);


    midLayout = new QVBoxLayout();
    mainLayout->addLayout(midLayout, 17);
    btnsLayout = new QHBoxLayout();
    cardsLayout = new QHBoxLayout();
    cardsWidget = new CardsWidget();
    cardsWidget->initail(17);
    cardsWidget->setMinimumWidth(400);
    cardsLayout->addWidget(cardsWidget);
    cardsLayout->addStretch(1);
    midLayout->addLayout(btnsLayout);
    midLayout->addLayout(cardsLayout);

    rightLayout = new QVBoxLayout();
    mainLayout->addLayout(rightLayout);
    timeRecoder = new QLCDNumber();
    rightLayout->addWidget(timeRecoder);
}

QWidget *Controller::widget()
{
    return desk;
}

CardsWidget *Controller::getCardsWidget() const
{
    return cardsWidget;
}

void Controller::connectSignals(MahjongJudgment* judgment)
{
    connect(judgment, &MahjongJudgment::updateTime, this, &Controller::onUpdateTime);
    connect(judgment, &MahjongJudgment::makeHappyGroup, this, &Controller::onMakeHappyGroup);
    connect(judgment, &MahjongJudgment::firstStep, this, &Controller::onFirstStep);
    connect(judgment, &MahjongJudgment::secondStep, this, &Controller::onSecondStep);
}

void Controller::onUpdateTime(unsigned sec)
{
    timeRecoder->display((int)sec);
}

void Controller::onMakeHappyGroup()
{
    cardsWidget->setMode(CardsWidget::CSM_LIAOXI);
    hideAllButtons();
    QList<PlayerOperation> operations;
    operations.push_back(PO_LIAOXI);
    operations.push_back(PO_OK);
    showButtonsOnly(operations);
}

void Controller::onFirstStep(QList<PlayerOperation> operations)
{
    cardsWidget->setMode(CardsWidget::CSM_CHI);
    showButtonsOnly(operations);
}

void Controller::onSecondStep(QList<PlayerOperation> operations)
{
    cardsWidget->setMode(CardsWidget::CSM_CUSTOM);
    showButtonsOnly(operations);
}

void Controller::onUpdatedDrawedCard(PaperCard *card)
{
    otherPlayersCard = card;
}
