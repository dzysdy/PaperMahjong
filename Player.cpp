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
#include <QApplication>

Player::Player(PaperMahjong* mahjong, const QString& playerName, int controllerType, QObject *parent) :
    QObject(parent),
    paperMahjong(mahjong),
    name(playerName),
    controller(ControllerFactory::createController((ControllerType)controllerType, this)),
    cardModel(new CardModel()),
    paperCards(cardModel->cards),
    algorithm(MahjongAlgorithmWraper::instance())
{
    cardModel->setFaceUp(controllerType == 0);
   // moveToThread(QApplication::instance()->thread());
}

Player::~Player()
{
    delete controller;
    delete cardModel;
}

void Player::initCards(const QList<PaperCard *>& cards)
{
    step = -1;
    groupCount = 0;
    cardModel->setData(cards);
    std::sort(paperCards.begin(), paperCards.end(), [](PaperCard* pc1, PaperCard* pc2){return *pc1 < *pc2;});
    controller->getCardsView()->setModel(cardModel);
}

PaperCard* Player::drawsCard() {
    PaperCard* card = paperMahjong->getCard();
    if (card) {
        card->setSelected(true);
        addCardToModel(card);
    }
    lastOperation = PO_DRAW;
    return card;
}

bool Player::discard()
{
    QList<PaperCard *> cards = getSelectedCards();
    if (cards.size() == 1) {
        removeCardsFromModel(cards);
        emit controller->updateDrawedArea(cards.first());
        lastOperation = PO_DISCARD;
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
        emit winningHand(this);
        return true;
    }
    return false;
}

void Player::makeHappyGroupOk()
{
    groupCount = (17 - paperCards.size())/3;
    emit makeHappyGroupCompleted();
}

void Player::doFirstStep(int /*operation*/)
{
    step = 1;
}

void Player::doSecondStep(int /*operation*/)
{
    step = 2;
}

QWidget *Player::desk()
{
    return controller->widget();
}

void Player::notifyStepCompleted()
{
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

int Player::getGroupCount() const
{
    return groupCount;
}

QString Player::getName() const
{
    return name;
}

int Player::getStep() const
{
    return step;
}

Controller *Player::getController() const
{
    return controller;
}
