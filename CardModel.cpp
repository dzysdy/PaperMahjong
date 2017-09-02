#include "CardModel.h"
#include "PaperCard.h"
#include "Player.h"

CardModel::CardModel(QObject *parent):
    QObject(parent)
{

}

CardModel::~CardModel()
{
    destroy();
}

void CardModel::update()
{
    emit updated();
}

QList<PaperCard *> CardModel::data()
{
    return cards;
}

void CardModel::setData(const QList<PaperCard *> &data)
{
    destroy();
    cards = data;
}

void CardModel::destroy()
{
    for (PaperCard* card: cards) {
        delete card;
    }
    cards.clear();
}
