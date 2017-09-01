#include "Player.h"
#include "MahjongJudgment.h"
#include "PaperMahjong.h"
#include "PaperCard.h"
#include "MahjongAlgorithmWraper.h"
#include "WorkDesk.h"
#include "AIController.h"
#include "CardView.h"
#include "CardModel.h"
#include "ControllerFactory.h"
#include <algorithm>

Player::Player(PaperMahjong* mahjong, MahjongJudgment *judgment, int controllerType, QObject *parent) :
    QObject(parent),
    paperMahjong(mahjong),
    controller(ControllerFactory::createController((ControllerType)controllerType, this)),
    cardModel(new CardModel()),
    paperCards(cardModel->cards),
    algorithm(MahjongAlgorithmWraper::instance())
{
    controller->connectSignals(judgment);
}

Player::~Player()
{
    delete controller;
    delete cardModel;
}

void Player::initCards(const QList<PaperCard *>& cards)
{
    cardModel->setData(cards);
    std::sort(paperCards.begin(), paperCards.end(), [](PaperCard* pc1, PaperCard* pc2){return *pc1 < *pc2;});
    controller->getCardsView()->setModel(cardModel);
}

PaperCard* Player::drawsCard() {
    PaperCard* card = paperMahjong->getCard();
    card->setSelected(true);
    addCardToModel(card);
    lastOperation = PO_DRAW;
    notifyStepCompleted();
    return card;
}

bool Player::discard()
{
    QList<PaperCard *> cards = getSelectedCards();
    if (cards.size() == 1) {
        removeCardsFromModel(cards);
        emit controller->updateDrawedArea(cards.first());
        lastOperation = PO_DISCARD;
        notifyStepCompleted();
        return true;
    }
    return false;
}

bool Player::chows(PaperCard* drawedCard)
{
    QList<PaperCard *> cards = getSelectedCards();
    cards.push_back(drawedCard);
    if (algorithm->isChow(cards)) {
        removeCardsFromModel(cards);
        controller->moveToCardGroupArea(cards);
        lastOperation = PO_CHOWS;
        notifyStepCompleted();
        return true;
    }
    return false;
}

bool Player::pongs(PaperCard* drawedCard)
{
    QList<PaperCard *> cards = getSelectedCards();
    cards.push_back(drawedCard);
    if (algorithm->isMelds(cards)) {
        removeCardsFromModel(cards);
        controller->moveToCardGroupArea(cards);
        lastOperation = PO_PONGS;
        notifyStepCompleted();
        return true;
    }
    return false;
}

bool Player::makePair(PaperCard* drawedCard)
{
    QList<PaperCard *> cards = getSelectedCards();
    cards.push_back(drawedCard);
    if (algorithm->isPair(cards)) {
        removeCardsFromModel(cards);
        controller->moveToCardGroupArea(cards);
        lastOperation = PO_PAIR;
        notifyStepCompleted();
        return true;
    }
    return false;
}

bool Player::makeHappyGroup()
{
    QList<PaperCard *> cards = getSelectedCards();
    if (algorithm->isHappyGroup(cards)) {
        controller->moveToCardGroupArea(cards);
        removeCardsFromModel(cards);
        lastOperation = PO_MAKEGROUP;
        return true;
    }
    return false;
}

bool Player::attachHappyGroup()
{
    return false;
}

bool Player::testWinning(PaperCard *drawedCard)
{
    QList<PaperCard*> cards(paperCards);
    if (drawedCard)
        cards.push_back(drawedCard);
    if (algorithm->isWinningHand(cards)){
        lastOperation = PO_WIN;
        return true;
    }
    return false;
}

void Player::makeHappyGroupOk()
{
    controller->setMyTurn(false);
    emit makedHappyGroup();
}

void Player::doFirstStep(int /*operation*/)
{
    controller->setMyTurn(true);
    step = 1;
}

void Player::doSecondStep(int /*operation*/)
{
    controller->setMyTurn(true);
    step = 2;
}

QWidget *Player::desk()
{
    return controller->widget();
}

void Player::onMakeHappyGroup()
{
    controller->setMyTurn(true);
}

void Player::notifyStepCompleted()
{
    controller->setMyTurn(false);
    if (step == 1) {
        emit firstStepCompleted(lastOperation);
    }
    else if (step == 2) {
        emit secondStepCompleted(lastOperation);
    }
}

QList<PaperCard *> Player::getSelectedCards()
{
    QList<PaperCard *> cards;
    for (PaperCard* card: paperCards) {
        if (card->isSelected()) {
            cards.push_back(card);
        }
    }
    return cards;
}

void Player::addCardToModel(PaperCard *card) {
//    auto itor = std::find_if(paperCards.begin(), paperCards.end(), [card](PaperCard* pc) {
//        return pc->getCardNumber() > card->getCardNumber();
//    });
//    paperCards.insert(itor - paperCards.begin(), card);
    paperCards.push_back(card);
    cardModel->update();
}

void Player::removeCardsFromModel(const QList<PaperCard *> &cards)
{
    bool updated = false;
    for (PaperCard* card: cards) {
        if (paperCards.contains(card)) {
            paperCards.removeOne(card);
            updated = true;
        }
    }
    std::sort(paperCards.begin(), paperCards.end(), [](PaperCard* pc1, PaperCard* pc2){return *pc1 < *pc2;});

    if (updated)
        cardModel->update();
}

int Player::getStep() const
{
    return step;
}

Controller *Player::getController() const
{
    return controller;
}
