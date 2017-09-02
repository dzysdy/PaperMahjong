#include "PaperMahjong.h"
#include "PaperCard.h"

PaperMahjong::PaperMahjong(QObject *parent) : QObject(parent)
{
}

void PaperMahjong::shuffleCards() {
    cardNumbers.clear();
    initCustomCard(PaperCard::CT_DOTS);
    initCustomCard(PaperCard::CT_BAMBOO);
    initCustomCard(PaperCard::CT_CHARACTERS);
    initFourCards(PaperCard::CT_REDFLOWER);
    initFourCards(PaperCard::CT_WHITEFLOWER);
    initFourCards(PaperCard::CT_SHARKS);
}

void PaperMahjong::dealingCards(unsigned num, QList<PaperCard *> &paperCards) {
    while (num--) {
        paperCards.push_back(getCard());
    }
}

PaperCard *PaperMahjong::getCard() {
    int randIndex = qrand()%cardNumbers.size();
    unsigned cardNumber = cardNumbers.takeAt(randIndex);
    return new PaperCard(cardNumber);
}

void PaperMahjong::initCustomCard(unsigned begin) {
    for (unsigned i = begin; i < begin + 9; ++i) {
        initFourCards(i);
    }
}

void PaperMahjong::initFourCards(unsigned cardNumber)
{
    for (unsigned i = 0; i < 4; ++i) {
        cardNumbers.push_back(cardNumber);
    }
}
