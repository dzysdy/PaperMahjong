#include "CardModel.h"
#include "PaperCard.h"
#include "Player.h"

CardModel::CardModel(QObject *parent):
    QObject(parent)
{

}

CardModel::~CardModel()
{
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
    cards = data;
}

