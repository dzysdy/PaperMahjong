#include "Player.h"
#include "MahjongJudgment.h"
#include "PaperMahjong.h"
#include "PaperCard.h"
#include "MajhongAlgorithmWraper.h"
#include "WorkDesk.h"
#include "AIController.h"
#include "CardsWidget.h"
#include <algorithm>

Player::Player(PaperMahjong* mahjong, MahjongJudgment *judgment, QObject *parent) :
    QObject(parent),
    paperMahjong(mahjong),
    algorithm(MajhongAlgorithmWraper::instance())
{
    controller = new WorkDesk(this);
    controller->connectSignals(judgment);
}

void Player::initCards(const QList<PaperCard *>& cards)
{
    paperCards.append(cards);
    std::sort(paperCards.begin(), paperCards.end(), [](PaperCard* pc1, PaperCard* pc2){return *pc1 < *pc2;});
    controller->getCardsWidget()->addCard(paperCards);
}

PaperCard* Player::drawsCard() {
    PaperCard* card = paperMahjong->getCard();
    addOneCard(card);
    lastOperation = PO_MO;
    notifyStepCompleted();
    return card;
}

bool Player::removeCard(PaperCard* card)
{
    paperCards.removeOne(card);
    lastOperation = PO_DA;
    notifyStepCompleted();
    return true;
}

bool Player::eat(const QList<PaperCard*>& cards)
{
    if (algorithm->is3Straight(cards)) {
        lastOperation = PO_EAT;
        notifyStepCompleted();
        return true;
    }
    return false;
}

bool Player::doubleEat(const QList<PaperCard*>& cards)
{
    if (algorithm->is3Pairs(cards)) {
        lastOperation = PO_PENG;
        notifyStepCompleted();
        return true;
    }
    return false;
}

bool Player::singleEat(const QList<PaperCard *> &cards)
{
    if (algorithm->is2Pairs(cards)) {
        lastOperation = PO_DING;
        notifyStepCompleted();
        return true;
    }
    return false;
}

bool Player::makeHappyGroup(const QList<PaperCard* >& cards)
{
    if (algorithm->isHappyGroup(cards)) {
        lastOperation = PO_LIAOXI;
        return true;
    }
    return false;
}

void Player::makeHappyGroupOk()
{
    controller->showBtnWidget(false);
    emit makedHappyGroup();
}

void Player::doFirstStep(int /*operation*/)
{
    controller->showBtnWidget(true);
    step = 1;
}

void Player::doSecondStep(int /*operation*/)
{
    controller->showBtnWidget(true);
    step = 2;
}

QWidget *Player::desk()
{
    return controller->widget();
}

void Player::onMakeHappyGroup()
{
    controller->showBtnWidget(true);
}

void Player::addOneCard(PaperCard *card) {
    auto itor = std::find_if(paperCards.begin(), paperCards.end(), [card](PaperCard* pc) {
        return pc->getCardNumber() > card->getCardNumber();
    });
    paperCards.insert(itor - paperCards.begin(), card);
}

void Player::notifyStepCompleted()
{
    controller->showBtnWidget(false);
    if (step == 1) {
        emit firstStepCompleted(lastOperation);
    }
    else if (step == 2) {
        emit secondStepCompleted(lastOperation);
    }
}

Controller *Player::getController() const
{
    return controller;
}
