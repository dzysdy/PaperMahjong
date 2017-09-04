#include "CardModel.h"
#include "PaperCard.h"
#include "Player.h"

CardModel::CardModel(QObject *parent):
    QObject(parent),
    faceUp(true)
{

}

CardModel::~CardModel()
{
}

void CardModel::update()
{
    emit updated();
}

const QList<PaperCard *>& CardModel::data()
{
    return cards;
}

void CardModel::setData(const QList<PaperCard *> &data)
{
    cards = data;
}

bool CardModel::getFaceUp() const
{
    return faceUp;
}

void CardModel::setFaceUp(bool value)
{
    faceUp = value;
}

