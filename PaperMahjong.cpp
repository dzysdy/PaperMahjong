#include "PaperMahjong.h"
#include "PaperCard.h"
#include <assert.h>

PaperMahjong::PaperMahjong(QObject *parent) :
    QObject(parent),
    shuffled(false)
{
}

void PaperMahjong::shuffleCards() {
    shuffled = true;
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
    assert(shuffled);
    if (cardNumbers.empty()) {
        emit draws();
        return nullptr;
    }
    int randIndex = qrand()%cardNumbers.size();
    unsigned cardNumber = cardNumbers.takeAt(randIndex);
    PaperCard* card = new PaperCard(cardNumber);
    dealedCards.push_back(card);
    return card;
}

void PaperMahjong::destoryDealedCards()
{
    for (PaperCard* card: dealedCards) {
        delete card;
    }
    dealedCards.clear();
    shuffled = false;
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
