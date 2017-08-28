#include "CardView.h"
#include "CardContainer.h"
#include "PaperCard.h"
#include "CardModel.h"
#include "Util.h"
#include <QHBoxLayout>
#include <QDebug>

CardView::CardView(QWidget *parent):
    QWidget(parent),
    model(nullptr),
    layout(nullptr)
{
}

void CardView::initail(unsigned num)
{
    if (layout)
        return;
    layout = new QHBoxLayout(this);
    while (num--) {
        CardContainer* cardContainer = new CardContainer();
        layout->addWidget(cardContainer);
        cardContainers.push_back(cardContainer);
        connect(cardContainer, &CardContainer::clicked, this, &CardView::onCardClicked);
    }
}

void CardView::setModel(CardModel *cardModel)
{
    model = cardModel;
    update();
    connect(model, &CardModel::updated, this, &CardView::onUpdated);
}

void CardView::update()
{
    showData(model->data());
}

void CardView::onUpdated()
{
    update();
}

void CardView::onCardClicked()
{}

void CardView::showData(QList<PaperCard *> data)
{
    for (int i = 0; i < cardContainers.size(); i++) {
        PaperCard* card = cardContainers[i]->getPaperCard();
        if (i < data.size()) {
            PaperCard* newCard = data[i];
            if (newCard != card) {
                cardContainers[i]->setCard(newCard);
            }
        }
        else {
            cardContainers[i]->setCard(nullptr);
        }
    }
}
